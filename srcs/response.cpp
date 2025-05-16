/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:01:30 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 19:19:42 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::string	html_response(std::string path, int status)
{
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	std::string hello_html;
	int home_html_fd = open((path.erase(0, 2)).c_str(), O_RDONLY);
	if (home_html_fd < 0) {
		std::cerr << "Error opening " << path << ": " << strerror(errno) << std::endl;
		std::string error_resp = 
		"HTTP/1.1 500 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 60\r\n"
		"Connection: keep-alive\r\n"
		"\r\n"
		"<html><body><h1>500 Internal Server Error</h1></body></html>";
		return error_resp;
	}
	ssize_t bytes_read = read(home_html_fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0) {
		std::cerr << "Error reading  " << path << ": " << strerror(errno) << std::endl;
		close(home_html_fd);
		std::string error_resp = 
		"HTTP/1.1 500 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: 60\r\n"
		"Connection: keep-alive\r\n"
		"\r\n"
		"<html><body><h1>500 Internal Server Error</h1></body></html>";
		return error_resp;
	}
	buffer[bytes_read] = '\0';
	hello_html = buffer;
	std::ostringstream cont_length;
	cont_length << hello_html.length();
	close(home_html_fd);
	// Send a simple response
	std::stringstream s_code;
	s_code << status;
	std::string response = 
		"HTTP/1.1 " + s_code.str() + " OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + cont_length.str() + "\r\n"
		"Connection: keep-alive\r\n"
		"\r\n"
		"" + hello_html + "";
		// "<html><body><h1>Hello from WebServ!</h1><p>Your request was received.</p></body></html>";
	return response;
}

std::string	server_response(std::string request, Config *config)
{
	std::istringstream iss(request);
	std::string method, path, version;
	iss >> method >> path >> version;

	std::cout << GREEN"Metodo: " << method << std::endl;
	std::cout << "Path: " << path << std::endl;
	std::cout << "Versione: " << version << std::endl;
	std::cout << RED "--" END << config->searchPath(path) << std::endl;
	std::string find_path = config->searchPath(path);
	if (path == "/favicon.ico")
		return "HTTP/1.1 204 No Content\r\n\r\n";
	else if (find_path != "")
		return html_response(find_path, 200);
	else
		return html_response(config->getRoot() + "/" + config->getError_page(), 404);
}
