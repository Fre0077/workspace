/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:01:30 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 08:19:12 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::string	home_response()
{
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	std::string home_html;
	int home_html_fd = open("srcs/server/home.html", O_RDONLY);
	if (home_html_fd < 0) {
		std::cerr << "Error opening home.html: " << strerror(errno) << std::endl;
		return NULL;
	}
	ssize_t bytes_read = read(home_html_fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0) {
		std::cerr << "Error reading home.html: " << strerror(errno) << std::endl;
		close(home_html_fd);
		return NULL;
	}
	buffer[bytes_read] = '\0';
	home_html = buffer;
	std::ostringstream cont_length;
	cont_length << home_html.length();
	close(home_html_fd);
	// Send a simple response
	std::string response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + cont_length.str() + "\r\n"
		"Connection: keep-alive\r\n"
		"\r\n"
		"" + home_html + "";
		// "<html><body><h1>Hello from WebServ!</h1><p>Your request was received.</p></body></html>";
	return response;
}

std::string	hello_response()
{
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	std::string hello_html;
	int home_html_fd = open("srcs/server/hello.html", O_RDONLY);
	if (home_html_fd < 0) {
		std::cerr << "Error opening hello.html: " << strerror(errno) << std::endl;
		return NULL;
	}
	ssize_t bytes_read = read(home_html_fd, buffer, sizeof(buffer) - 1);
	if (bytes_read < 0) {
		std::cerr << "Error reading hello.html: " << strerror(errno) << std::endl;
		close(home_html_fd);
		return NULL;
	}
	buffer[bytes_read] = '\0';
	hello_html = buffer;
	std::ostringstream cont_length;
	cont_length << hello_html.length();
	close(home_html_fd);
	// Send a simple response
	std::string response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Content-Length: " + cont_length.str() + "\r\n"
		"Connection: keep-alive\r\n"
		"\r\n"
		"" + hello_html + "";
		// "<html><body><h1>Hello from WebServ!</h1><p>Your request was received.</p></body></html>";
	return response;
}

std::string	server_response(std::string request)
{
	std::istringstream iss(request);
	std::string method, path, version;
	iss >> method >> path >> version;

	std::cout << "Metodo: " << method << std::endl;
	std::cout << "Path: " << path << std::endl;
	std::cout << "Versione: " << version << std::endl;
	if (path == "/favicon.ico")
		return "HTTP/1.1 204 No Content\r\n\r\n";
	else if (path == "/hello")
		return hello_response();
	else
		return home_response();
}