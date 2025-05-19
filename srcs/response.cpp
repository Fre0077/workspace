/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:01:30 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/19 15:27:50 by fde-sant         ###   ########.fr       */
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

std::string	server_response(Request *request, Config *config)
{
	std::string method = request->getMethod(), path = request->getPath();
	std::string find_path = config->searchPathI(path);

	std::cout << GREEN "--" << find_path << "--" END << std::endl;
	if (path == "/favicon.ico")
		return "HTTP/1.1 204 No Content\r\n\r\n";
	else if (method != "GET" && method != "DELETE" && method != "POST")
		return html_error(501, config);
	else if (find_path == "")
		return html_error(404, config);
	else
		return html_response(find_path, 200, config);
}
