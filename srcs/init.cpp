/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:57:32 by fde-sant          #+#    #+#             */
/*   Updated: 2025/09/16 22:25:54 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"
#include <set>

int	init_server_socket(int *server_fd, Config &config)
{
	// 1. Create a socket
	*server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (*server_fd < 0)
	{
		std::cerr << "Error opening socket: " << strerror(errno) << std::endl;
		return 1;
	}

	// 2. Set socket options
	int opt = 1;
	if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		std::cerr << "Error setting socket options: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}

	// 3. Bind to address and port
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	address.sin_port = htons(stringToInt(config.getPort()));
	if (bind(*server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		std::cerr << "Error binding socket: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1; 	
	}

	// 4. Listen for connections
	if (listen(*server_fd, 10) < 0)
	{
		std::cerr << "Error listening: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}

	if (fcntl(*server_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		std::cerr << "Error setting non-blocking mode: " << strerror(errno) << std::endl;
		close(*server_fd);
		return 1;
	}
	return 0;
}

int	get_number_server(std::string file_name)
{
	std::ifstream	file(file_name.c_str());
	std::string		line;
	int				n_server = 0;

	while (std::getline(file, line))
		if (line.find("server") == 0)
			n_server++;
	return n_server;
}

int	init_config(std::string file_name, std::map<int, Config*> &configs, std::vector<pollfd> *pollfds, int n_server, int &n_socket)
{
	int	server_fd;
	int new_servern = 0;
	std::map <std::string, std::string> cgi = init_cgi_types();
	std::map<int, int> used_ports; // Per tracciare le porte già usate
	
	for(int i = 1; i <= n_server; i++)
	{
		Config *config = new Config(file_name, i, cgi);
		
		for (std::map<int, Config*>::iterator it = configs.begin(); it != configs.end(); ++it)
		{
			if (it->second->getServer_name() == config->getServer_name())
			{
				std::cerr << RED "Error: duplicate server_name '" << config->getServer_name() << "'" END << std::endl;
				delete config;
				return 1;
			}
		}
		
		configs[i] = config;
		
		int port = atoi(config->getPort().c_str());
		
		// Controlla se esiste già un socket per questa porta
		if (used_ports.find(port) == used_ports.end())
		{
			// Prima volta che vediamo questa porta, crea il socket
			if (init_server_socket(&server_fd, *config) != 0)
				return 1;
			pollfd server_pollfd;
			server_pollfd.fd = server_fd;
			server_pollfd.events = POLLIN;
			server_pollfd.revents = 0;
			(*pollfds).push_back(server_pollfd);
			used_ports[port] = server_fd;
			config->setFd(server_fd);
			new_servern++;
			std::cout << GREEN "Created socket for port " << config->getPort() << " (server: " << config->getServer_name() << ")" << END << std::endl;
		}
		else
		{
			config->setFd(used_ports[port]);
			std::cout << YELLOW "Port " << config->getPort() << " already has socket, sharing for server: " << config->getServer_name() << END << std::endl;
		}
	}
	n_socket = new_servern;
	return 0;
}