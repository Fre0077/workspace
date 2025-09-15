/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:01:30 by fde-sant          #+#    #+#             */
/*   Updated: 2025/09/15 18:17:53 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::string	html_response(const std::string& path, int status, Config *config, std::string content_type)
{
	std::ifstream file(path.c_str(), std::ios::binary);
	if (!file.is_open())
	{
		file.close();
		std::cerr << "Error opening " << path << ": " << strerror(errno) << std::endl;
		return config->getDError_page(500);
	}

	std::ostringstream ss;
	ss << file.rdbuf();	
	std::string file_data = ss.str();
	std::stringstream s_code;
	s_code << status;
	std::ostringstream headers;
	headers << "HTTP/1.1 " + s_code.str() + " OK\r\n";
	headers << "Content-Type: " + content_type + "\r\n";
	headers << "Content-Length: " << file_data.size() << "\r\n";
	headers << "Connection: keep-alive\r\n";
	headers << "\r\n";

	std::string response = headers.str() + file_data;
	file.close();
	return response;
}

std::string	html_error(int err, Config *config)
{
	if (config->getError_page(err) == "")
		return config->getDError_page(err);
	else
		return html_response(config->getRoot() + "/" + config->getError_page(err), err, config, "text/html");
}

int save_file(Request *request, std::string path)
{
	if (request->getBody() == "")
	{
		std::cerr << RED "Body not found in request" << END << std::endl;
		return 1;
	}
	std::ofstream file((path + request->getFileName()).c_str(), std::ios::binary);
	if (!file.is_open())
	{
		file.close();
		std::cerr << RED "Error opening " << request->getFileName() << ": " << strerror(errno) << "" END << std::endl;
		return 2;
	}
	file.write(request->getBody().c_str(), request->getBody().size());
	file.close();
	return 0;
}

std::string extension(const std::string& path)
{
	size_t dotPos = path.rfind('.');
	if (dotPos == std::string::npos)
		return "";
	return path.substr(dotPos);
}

// Add helper function to create CGI response
std::string create_cgi_response(const std::string& cgi_output)
{
    std::ostringstream headers;
    headers << "HTTP/1.1 200 OK\r\n";
    headers << "Content-Type: text/plain\r\n";  // Use text/plain for CGI output
    headers << "Content-Length: " << cgi_output.size() << "\r\n";
    headers << "Connection: keep-alive\r\n";
    headers << "\r\n";
    
    return headers.str() + cgi_output;
}

std::string	server_response(Request *request, Config *config)
{
	std::string method = request->getMethod(), path = request->getPath();
	
	std::cout << GREEN "" << request->getPath() <<"" END << std::endl;
	std::cout << GREEN "----------" << config->checkPath(path) <<"---------" END << std::endl;
	std::cout << GREEN "----------" << request->checkPathFile() <<"---------" END << std::endl;
	if (path == "/favicon.ico")
		return "HTTP/1.1 204 No Content\r\n\r\n";
	else if (config->getMax_body_len() <= request->getBodyLength())
		return html_error(413, config);
	else if (config->checkPath(path) && request->checkPathFile())
		return html_error(404, config);
	else if (((!(request->getMethodNum() & config->getLocationMethod(path)) || config->getLocationMethod(path) == 8) && config->getLocationMethod(path) != 0) || (!(request->getMethodNum() & config->getMethod()) && config->getLocationMethod(path) == 0))
		return html_error(405, config);
	else if (method != "GET" && method != "DELETE" && method != "POST")
		return html_error(501, config);
	else if (!config->checkPath(path))
	{
		if (method == "DELETE")
		{
			std::string full_path = "./srcs/server/upload/" + request->getDeleteFile();
			if (remove(full_path.c_str()) == 0)
			{
				return html_response(config->getLocationIndex("/delete"), 200, config, "text/html");
			}
			else
			{
				std::cerr << RED "Error deleting file: " << strerror(errno) << "" END << std::endl;
				return html_error(404, config);
			}
		}
		else if (path == "/upload" && method == "POST")
		{
			int ret = save_file(request, config->getLocationUpload(path));
			std::cout << RED "ret: " END << ret << std::endl;
			if (ret == 1)
				return html_error(400, config);
			else if (ret == 2)
				return html_error(406, config);
		}
		else if (method == "POST" && extension(path) == ".pl")
		{
			std::string full_path = config->getLocationRoot(path) + path;  // Fix path construction
			std::cout << RED "Executing " << full_path << " file..." END << std::endl;
			
			if (access(full_path.c_str(), F_OK) != 0)
			{
				std::cerr << RED "File not found: " << full_path << "" END << std::endl;
				return html_error(404, config);
			}
			
			std::string result = exec_perl(full_path);
			if (result.empty())
			{
				std::cerr << RED "CGI execution failed or returned empty result" << END << std::endl;
				return html_error(500, config);
			}
			
			std::cout << RED "CGI Output:\n" << result << END << std::endl;
			return create_cgi_response(result);
		}
		else if (method == "POST" && extension(path) == ".py")
		{
			std::string full_path = config->getLocationRoot(path) + path;  // Fix path construction
			std::cout << RED "Executing " << full_path << " file..." END << std::endl;
			
			if (access(full_path.c_str(), F_OK) != 0)
			{
				std::cerr << RED "File not found: " << full_path << "" END << std::endl;
				return html_error(404, config);
			}
			
			std::string result = exec_py(full_path);
			if (result.empty())
			{
				std::cerr << RED "CGI execution failed or returned empty result" << END << std::endl;
				return html_error(500, config);
			}
			
			std::cout << RED "CGI Output:\n" << result << END << std::endl;
			return create_cgi_response(result);
		}
		return html_response(config->getLocationIndex(path), 200, config, "text/html");
	}
	else if (path.find(".mp4") != std::string::npos)
		return html_response("." + path, 200, config, "video/mp4");
	else
		return html_response("." + path, 200, config, "");
}
