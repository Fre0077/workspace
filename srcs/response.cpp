/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:01:30 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/20 16:47:10 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::string	html_response(std::string path, int status, Config *config, std::string content_type, std::string connection)
{
	std::ifstream file(path.c_str(), std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "Error opening " << path << ": " << strerror(errno) << std::endl;
		return config->getDError_page(500);
	}

	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::string _html(size, '\0');
	if (!file.read(&_html[0], size)) {
		std::cerr << "Error reading " << path << ": " << strerror(errno) << std::endl;
		return config->getDError_page(500);
	}

	std::ostringstream cont_length;
	cont_length << size;

	std::stringstream s_code;
	s_code << status;
	
	std::string response = 
		"HTTP/1.1 " + s_code.str() + " OK\r\n"
		"Content-Type: " + content_type + "\r\n"
		"Content-Length: " + cont_length.str() + "\r\n"
		"Connection: " + connection + "\r\n"
		"\r\n" + _html;
	
	return response;
}

std::string html_image(const std::string& path, int status, Config *config)
{
	std::ifstream file(path.c_str(), std::ios::binary);
	
	std::cout << RED "----------" << path <<"---------" END << std::endl;
	if (!file.is_open())
	{
		file.close();
		std::cerr << "Error opening " << path << ": " << strerror(errno) << std::endl;
		return config->getDError_page(500);
	}

	// Leggi il contenuto del file immagine
	std::ostringstream ss;
	ss << file.rdbuf();
	std::string file_data = ss.str();

	// Costruisci gli header HTTP
	std::stringstream s_code;
	s_code << status;
	std::ostringstream headers;
	headers << "HTTP/1.1 " + s_code.str() + " OK\r\n";
	headers << "Content-Type: image/jpeg\r\n";
	headers << "Content-Length: " << file_data.size() << "\r\n";
	headers << "Connection: close\r\n";
	headers << "\r\n";

	// Unisci header + contenuto binario dell'immagine
	std::string response = headers.str() + file_data;
	file.close();
	return response;
}

std::string	html_video(const std::string& path, int status, Config *config)
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
	headers << "Content-Type: video/mp4\r\n";
	headers << "Content-Length: " << file_data.size() << "\r\n";
	headers << "Connection: close\r\n";
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
		return html_response(config->getRoot() + "/" + config->getError_page(err), err, config, "text/html", "keep-alive");
}

std::string	server_response(Request *request, Config *config)
{
	std::string method = request->getMethod(), path = request->getPath();
	
	std::cout << GREEN "" << request->getPath() <<"" END << std::endl;
	std::cout << GREEN "----------" << config->checkPath(path) <<"---------" END << std::endl;
	if (path == "/favicon.ico")
		return "HTTP/1.1 204 No Content\r\n\r\n";
	else if (config->getMax_body_len() <= request->getBodyLength())
		return html_error(413, config);
	else if (path.find(".jpg") != std::string::npos)
		return html_image(config->getRoot() + path, 200, config);
	else if (path.find(".mp4") != std::string::npos)
		return html_video(config->getRoot() + path, 200, config);
	else if (config->checkPath(path))
		return html_error(404, config);
	else if (!(request->getMethodNum() & config->getLocationMethod(path)) || config->getLocationMethod(path) == 0)
		return html_error(405, config);
	else if (method != "GET" && method != "DELETE" && method != "POST")
		return html_error(501, config);
	else
		return html_response(config->getLocationIndex(path), 200, config, "text/html", "keep-alive");
}
