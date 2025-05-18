/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:01:30 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/18 09:53:37 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::string	html_response(std::string path, int status, Config *config)
{
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	std::string _html;
	int home_html_fd = open((path.erase(0, 2)).c_str(), O_RDONLY);
	if (home_html_fd < 0) {
		std::cerr << "Error opening " << path << ": " << strerror(errno) << std::endl;
		return config->getDError_page(500);
	}
	ssize_t bytes_read = read(home_html_fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0) {
		std::cerr << "Error reading  " << path << ": " << strerror(errno) << std::endl;
		close(home_html_fd);
		return config->getDError_page(500);
	}
	buffer[bytes_read] = '\0';
	_html = buffer;
	std::ostringstream cont_length;
	cont_length << _html.length();
	close(home_html_fd);
	std::stringstream s_code;
	s_code << status;
	std::string response = 
		"HTTP/1.1 " + s_code.str() + " OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + cont_length.str() + "\r\n"
		"Connection: keep-alive\r\n"
		"\r\n"
		"" + _html + "";
	return response;
}

std::string	html_error(int err, Config *config)
{
	if (config->getError_page(err) == "")
		return config->getDError_page(err);
	else
		return html_response(config->getRoot() + "/" + config->getError_page(err), err, config);
}

std::string	html_upload(int err, Config *config)
{
	if (config->getError_page(err) == "")
		return config->getDError_page(err);
	else
		return html_response(config->getRoot() + "/" + config->getError_page(err), err, config);
}

std::string	server_response(std::string request, Config *config)
{
	std::string method = config->getMethod(), path = config->getPath();
	std::string find_path = config->searchPathI(path);

	std::cout << GREEN"Metodo: " << method << std::endl;
	std::cout << "Path: " << path << std::endl;
	std::cout << "--" END << find_path << std::endl;
	if (path == "/favicon.ico")
		return "HTTP/1.1 204 No Content\r\n\r\n";
	else if (method == "POST" && path == "/upload")
	{
		config->changePushNeed();
		config->setLength(request);
		config->setBoundary(request);
		return html_error(404, config);
	}
	else if (method != "GET")
		return html_error(501, config);
	else if (find_path == "")
		return html_error(404, config);
	else
		return html_response(find_path, 200, config);
}

std::string	upload(std::string request, Config *config)
{
	(void)request;
	return config->getDError_page(500);
}