/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:34:58 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/18 09:59:41 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

int new_connection(int server_fd)
{
	// Accept a connection
	std::cout << CYAN "NEW CONNECTION" END << std::endl;
	struct sockaddr_in client_address;
	socklen_t client_addr_len = sizeof(client_address);
	int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len);
	if (client_fd < 0)
	{
		std::cerr << "Error accepting connection: " << strerror(errno) << std::endl;
		return 0;
	}
	int optval = 1;
	setsockopt(client_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Error setting non-blocking mode: " << strerror(errno) << std::endl;
		close(client_fd);
		return 0;
	}
	return client_fd;
}

int client_request(std::vector<pollfd> pollfds, Config *config, size_t *i)
{
	std::string request;
	char temp_buffer[8192];
	int	bytes = 1, bytes_read = 0;
	size_t body_len;

	while (request.find("\r\n\r\n") == std::string::npos)
	{
		bytes = recv(pollfds[*i].fd, temp_buffer, 8192, 0);
		if (bytes <= 0)
			break;
		bytes_read += bytes;
		request.append(temp_buffer, bytes);
	}
	config->setRequestType(request);
	config->setBoundary(request);
	config->setLength(request);
	config->checkConfig();
	body_len = request.size() - request.find("\r\n\r\n") + 4;
	while (body_len < config->getLength() && config->getMethod() == "POST")
	{
		bytes = recv(pollfds[*i].fd, temp_buffer, 8192, 0);
		if (bytes <= 0)
			continue;
		bytes_read += bytes;
		body_len += bytes;
		request.append(temp_buffer, bytes);
	}
	std::cout << MAGENTA "bytes_read: " << bytes_read << std::endl;
	std::cout << "Received data from client:\n" END << request << std::endl;
	if (bytes_read > 0)
	{
		std::string response = server_response(request, config);
		send(pollfds[*i].fd, response.c_str(), response.length(), 0);
	}
	else if (bytes_read == 0)
	{
		std::cout << "Client disconnected" << std::endl;
		close(pollfds[*i].fd);
		pollfds.erase(pollfds.begin() + *i);
		*i -= 1;
	}
	else if (bytes_read == -1)
	{
		std::cerr << "Errore nella lettura: " << strerror(errno) << std::endl;
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
		return 1;
	}
	Config config(argv[1]);
	std::cout << config << std::endl;
	int server_fd;
	if (init_server_socket(&server_fd, config) != 0)
	{
		return 1;
	}
	std::cout << "Server listening on port " << config.getPort() << std::endl;

	pollfd server_pollfd;
	server_pollfd.fd = server_fd;
	server_pollfd.events = POLLIN;
	server_pollfd.revents = 0;
	std::vector<pollfd> pollfds;
	pollfds.push_back(server_pollfd);

	// 5. Accept and handle connections
	while (1) {
		// Use select or poll to wait for incoming connections
		std::cout << YELLOW "=========================waiting for poll=============================" END << std::endl;
		int ret = poll(pollfds.data(), pollfds.size(), -1);
		if (ret < 0)
		{
			std::cerr << "Error in poll: " << strerror(errno) << std::endl;
			break;
		}
		
		//ciclo per la lettura della request e per degli errori del poll()
		size_t size = pollfds.size();
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << "i: " << i << std::endl;
			std::cout << "pollfds[i].fd: " << pollfds[i].fd << std::endl;
			std::cout << "pollfds[i].events: " << pollfds[i].events << std::endl;
			std::cout << "pollfds[i].revents: " << pollfds[i].revents << std::endl;
			if (pollfds[i].revents & POLLERR) //errore del poll
			{
				std::cerr << "Errore sul socket: " << pollfds[i].fd << std::endl;
				close(pollfds[i].fd);
				pollfds[i].fd = -1;
				pollfds.erase(pollfds.begin() + i);
				i--;
				size = pollfds.size();
				continue;
			}
			if (pollfds[i].revents & POLLHUP) //errore del poll
			{
				std::cout << "Connessione chiusa dal client: " << pollfds[i].fd << std::endl;
				close(pollfds[i].fd);
				pollfds.erase(pollfds.begin() + i);
				i--;
				size = pollfds.size();
				continue;
			}
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == server_fd) //connessione di un nuovo client
				{
					int fd = new_connection(server_fd);
					if (fd > 0)
					{
						pollfd client_pollfd;
						client_pollfd.fd = fd;
						client_pollfd.events = POLLIN;
						pollfds.push_back(client_pollfd);
					}
				}
				else
					if (client_request(pollfds, &config, &i)) //richiesta da un client già connesso
						return 1;
			}
			pollfds[i].revents = 0;
		}
	}
	close(server_fd);
	return 0;
}


//else if (config.pushNeed())
//{
//	config.changePushNeed();
//	std::cout << RED "legth: " END << config.getLength() << std::endl;
//	char buffer[config.getLength()];
//	memset(buffer, 0, sizeof(buffer));
//	ssize_t bytes_read;
//	bytes_read = recv(pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);
//	std::cout << MAGENTA "bytes_read: " END << bytes_read << std::endl;
//	std::cout << MAGENTA "Received data from client:\n" END << buffer << std::endl;
//	if (request.find(config.getBoundary() + "--") == std::string::npos)
//	{
//		request.append(buffer, config.getLength());
//		config.changePushNeed();
//		continue;
//	}
//	if (bytes_read > 0)
//	{
//		if (bytes_read == config.getLength() - 1)
//		{
//			std::cerr << "Buffer overflow" << std::endl;
//			close(pollfds[i].fd);
//			pollfds.erase(pollfds.begin() + i);
//			i--;
//			return 1;
//		}
//		std::string response = upload(buffer, &config);
//		send(pollfds[i].fd, response.c_str(), response.length(), 0);
//	}
//	else if (bytes_read == 0)
//	{
//		std::cout << "Client disconnected" << std::endl;
//		close(pollfds[i].fd);
//		pollfds.erase(pollfds.begin() + i);
//		i--;
//	}
//	else if (bytes_read == -1)
//	{
//		std::cerr << "Errore nella lettura: " << strerror(errno) << std::endl;
//	}
//}