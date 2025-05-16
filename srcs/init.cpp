/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 07:57:32 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 11:46:35 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

int	init_server_socket(int *server_fd)
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
	address.sin_addr.s_addr = INADDR_ANY; // Accept connections on any interface
	address.sin_port = htons(8080);       // Port from config (hardcoded for now)
		
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