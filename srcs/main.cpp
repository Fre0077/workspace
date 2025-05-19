/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:34:58 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/19 12:44:59 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

int new_connection(int server_fd)
{
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

int close_socket(std::vector<pollfd> *pollfds, size_t *i)
{
	std::cerr << RED "Client disconnected" END << std::endl;
	close((*pollfds)[*i].fd);
	(*pollfds).erase((*pollfds).begin() + *i);
	*i -= 1;
	return 0;
}

int client_request(std::vector<pollfd> *pollfds, Request *request, Config *config, size_t *i)
{
	char temp_buffer[8192];
	int	bytes_read = 0;

	//lettura dell'header
	if (request->checkHead())
	{
		bytes_read = recv((*pollfds)[*i].fd, temp_buffer, 8192, 0);
		if (bytes_read == 0)
			close_socket(pollfds, i);
		if (bytes_read < 0)
			return 0;
		request->setRequest(temp_buffer, bytes_read);
		if (request->checkHead())
			return 0;
		//acquisizioni dati dall'header
		request->setRequestType();
		request->setHeadLength();
		request->setBoundary();
		request->setLength();
	}
	std::cout << *request << std::endl;
	memset(temp_buffer, 0, sizeof(temp_buffer));
	//lettura del body se ce n'è bisogno
	if (request->checkBody())
	{
		bytes_read = recv((*pollfds)[*i].fd, temp_buffer, 8192, 0);
		if (bytes_read == 0)
			close_socket(pollfds, i);
		if (bytes_read < 0)
			return 0;
		request->setRequest(temp_buffer, bytes_read);
		if (request->checkBody())
			return 0;
	}
	std::cout << request->getRequest() << std::endl;
	//controllo il ritorno del recv
	if (bytes_read > 0)
	{
		//ritorno una risposta al sito
		std::string response = server_response(request, config);
		send((*pollfds)[*i].fd, response.c_str(), response.length(), 0);
	}
	else if (bytes_read == 0)
		close_socket(pollfds, i);
	else if (bytes_read == -1)
	{
		std::cerr << RED "Errore nella lettura: " END << strerror(errno) << std::endl;
	}
	request->clearRequest();
	return 0;
}

int main(int argc, char **argv)
{
	//controllo degli argomenti
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " <config file>" << std::endl;
		return 1;
	}
	//dichiarazione per la configurazioe e la reqeust
	Config					config(argv[1]);
	std::vector<Request>	requests;
	std::cout << config << std::endl;
	//inizializzazione del soicket per il server
	int server_fd;
	if (init_server_socket(&server_fd, config) != 0)
	{
		return 1;
	}
	std::cout << "Server listening on port " << config.getPort() << std::endl;
	//creare l'array per le struct del poll e aggiunto l'fd del server (0)
	pollfd server_pollfd;
	server_pollfd.fd = server_fd;
	server_pollfd.events = POLLIN;
	server_pollfd.revents = 0;
	std::vector<pollfd> pollfds;
	pollfds.push_back(server_pollfd);
	//loop per la gestione delle richieste
	while (1) {
		//check del poll per verificare lo stato delle request
		std::cout << YELLOW "=========================waiting for poll=============================" END << std::endl;
		int ret = poll(pollfds.data(), pollfds.size(), -1);
		if (ret < 0)
		{
			std::cerr << "Error in poll: " << strerror(errno) << std::endl;
			break;
		}
		//ciclo per la lettura della request dei singoli client
		size_t size = pollfds.size();
		for (size_t i = 0; i < size; ++i)
		{
			std::cout << "i: " << i << std::endl;
			std::cout << "pollfds[i].fd: " << pollfds[i].fd << std::endl;
			std::cout << "pollfds[i].events: " << pollfds[i].events << std::endl;
			std::cout << "pollfds[i].revents: " << pollfds[i].revents << std::endl;
			if (pollfds[i].revents & POLLERR || pollfds[i].revents == 32) //errore del poll, errore generico
			{
				close_socket(&pollfds, &i);
				size = pollfds.size();
				continue;
			}
			if (pollfds[i].revents & POLLHUP) //errore del poll, chiusura delle connessione
			{
				close_socket(&pollfds, &i);
				size = pollfds.size();
				continue;
			}
			if (pollfds[i].revents & POLLIN) //la request viene letta e gestita
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
						Request request;
						requests.push_back(request);
					}
				}
				else
					if (client_request(&pollfds, &requests[i - 1], &config, &i)) //richiesta da un client già connesso
						return 1;
			}
			pollfds[i].revents = 0;
		}
	}
	close(server_fd);
	return 0;
}
