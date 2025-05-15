/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:34:58 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/15 19:18:19 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

int	init_socket(int *server_fd)
{
	// 1. Create a socket
	*server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*server_fd < 0) {
		std::cerr << "Error opening socket: " << strerror(errno) << std::endl;
		return 1;
	}

	// 2. Set socket options
	int opt = 1;
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		std::cerr << "Error setting socket options: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}

	// 3. Bind to address and port
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // Accept connections on any interface
	address.sin_port = htons(8080);       // Port from config (hardcoded for now)
		
	if (bind(*server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		std::cerr << "Error binding socket: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}

	// 4. Listen for connections
	if (listen(*server_fd, 10) < 0) {
		std::cerr << "Error listening: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}

	if (fcntl(*server_fd, F_SETFL, O_NONBLOCK) < 0) {
		std::cerr << "Error setting non-blocking mode: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}
	return 0;
}

std::string home_response()
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
		// "Connection: close\r\n"
		"\r\n"
		"" + home_html + "";
		// "<html><body><h1>Hello from WebServ!</h1><p>Your request was received.</p></body></html>";
	return response;
}

int new_connection(int server_fd)
{
	// Accept a connection
	int optval = 1;
	struct sockaddr_in client_address;
	socklen_t client_addr_len = sizeof(client_address);
	int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len);
	if (client_fd < 0) {
		std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
		return 0;
	}

	setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1) {
		std::cerr << "Error setting non-blocking mode: " << strerror(errno) << std::endl;
		close(client_fd);
		return 0;
	}

	// Read request
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	ssize_t bytes_read = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
	// std::cout << "bytes_read: " << bytes_read << std::endl;
	
	if (bytes_read > 0) {
		std::cout << "Received request:" << std::endl;
		std::cout << buffer << std::endl;
		
		std::string response = home_response();
		if (response.empty()) {
			std::cerr << "Error creating response" << std::endl;
			close(client_fd);
			return 0;
		}

		send(client_fd, response.c_str(), response.length(), 0);
	}
	return client_fd;
}

int main(int argc, char **argv)
{
    if (argc != 2)
	{
        std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
        return 1;
    }
    
	int server_fd;
	if (init_socket(&server_fd) != 0)
	{
		return 1;
	}

    std::cout << "Server listening on port 8080" << std::endl;

	pollfd server_pollfd;
	server_pollfd.fd = server_fd;
	server_pollfd.events = POLLIN;
	server_pollfd.revents = 0;
	std::vector<pollfd> pollfds;
	pollfds.push_back(server_pollfd);

    // 5. Accept and handle connections
    while (1) {
		// Use select or poll to wait for incoming connections
		for (size_t i = 0; i < pollfds.size(); ++i)
		{
			std::cout << "======================================================================" << std::endl;
			std::cout << "i: " << i << std::endl;
			std::cout << "pollfds[i].fd: " << pollfds[i].fd << std::endl;
			std::cout << "pollfds[i].events: " << pollfds[i].events << std::endl;
			std::cout << "pollfds[i].revents: " << pollfds[i].revents << std::endl;
		}
		std::cout << "=============================waiting for poll=============================" << std::endl;
		int ret = poll(pollfds.data(), pollfds.size(), -1);
		if (ret < 0) {
			std::cerr << "Error in poll: " << strerror(errno) << std::endl;
			break;
		}
		std::cout << "=============================new poll=============================" << std::endl;
		size_t size = pollfds.size();
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << "======================================================================" << std::endl;
			std::cout << "i: " << i << std::endl;
			std::cout << "pollfds[i].fd: " << pollfds[i].fd << std::endl;
			std::cout << "pollfds[i].events: " << pollfds[i].events << std::endl;
			std::cout << "pollfds[i].revents: " << pollfds[i].revents << std::endl;
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == server_fd)
				{
					std::cout << "New connection" << std::endl;
					int fd = new_connection(server_fd);
					if (fd > 0)
					{
						pollfd client_pollfd;
						client_pollfd.fd = fd;
						client_pollfd.events = POLLIN;
						// client_pollfd.revents = 0;
						pollfds.push_back(client_pollfd);
					}
				}
				else
				{
					// Handle client connection
					char buffer[4096];
					memset(buffer, 0, sizeof(buffer));
					ssize_t bytes_read = recv(pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);
					std::cout << "bytes_read: " << bytes_read << std::endl;
					if (bytes_read > 0)
					{
						std::cout << "Received data from client: " << buffer << std::endl;
						// Process the request and send a response
						std::string response = home_response();
						send(pollfds[i].fd, response.c_str(), response.length(), 0);
					}
					else if (bytes_read == 0)
					{
						std::cout << "Client disconnected" << std::endl;
						close(pollfds[i].fd);
						pollfds.erase(pollfds.begin() + i);
						i--;
					}
				}
			}
			pollfds[i].revents = 0;
		}
		std::cout << "=============================end of poll=============================" << std::endl;
    }

    close(server_fd);
    return 0;
}