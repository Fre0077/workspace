/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:34:58 by alborghi          #+#    #+#             */
/*   Updated: 2025/09/17 18:10:17 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::map<std::string, std::string> init_cgi_types()
{
	std::map<std::string, std::string> cgi_types;
	cgi_types[".py"] = "/usr/bin/python3";
	cgi_types[".pl"] = "/usr/bin/perl";
	// cgi_types[".php"] = &exec_php;
	// cgi_types[".rb"] = &exec_ruby;
	// cgi_types[".sh"] = &exec_sh;
	// cgi_types[".js"] = &exec_js;
	// cgi_types[".html"] = &exec_html;
	// cgi_types[".htm"] = &exec_html;
	return cgi_types;
}

void	close_server(int sig)
{
	std::cout << RED "Server shutting down..." END << std::endl;
	if (sig == SIGINT)
	{
		std::cout << "SIGINT received" << std::endl;
		throw std::runtime_error("SIGINT received");
	}
	else if (sig == SIGQUIT)
		std::cout << "SIGQUIT received" << std::endl;
}

void	init_signals()
{
	signal(SIGINT, close_server);
	signal(SIGQUIT, SIG_IGN);
}

int new_connection(int server_fd)
{
	std::cout << CYAN "NEW CONNECTION" END << std::endl;
	struct sockaddr_in client_address;
	socklen_t client_addr_len = sizeof(client_address);
	std::cout << "server_fd = " << server_fd << std::endl;
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

int close_socket(std::vector<pollfd> *pollfds, std::vector<Request> *requests, size_t *i)
{
	std::cerr << RED "Client disconnected" END << std::endl;
	close((*pollfds)[*i].fd);
	(*pollfds).erase((*pollfds).begin() + *i);
	(void)requests;
	*i -= 1;
	return 0;
}

int	check_server_fd(int fd, int n_server, std::vector<pollfd> *pollfds)
{
	for(int i = 0; i < n_server; i++)
		if (fd == (*pollfds)[i].fd)
			return 1;
	return 0;
}

Config	*check_config(std::map<int, Config*> *configs, Request *request, int n_server)
{
	std::string request_hostname = request->getHostHeader();
	int request_port = request->getPortFromRequest();
	
	std::cout << GREEN "Looking for server: hostname=" << request_hostname << " port=" << request_port << END << std::endl;
	
	// Passo 1: Cerca corrispondenza esatta (porta + server_name)
	for(int i = 1; i <= n_server; i++)
	{
		if ((atoi((*configs)[i]->getPort().c_str())) == request_port && (*configs)[i]->getServer_name() == request_hostname)
		{
			std::cout << GREEN "Found exact match: " << (*configs)[i]->getServer_name() << END << std::endl;
			return (*configs)[i];
		}
	}
	
	// Passo 2: Se non trova corrispondenza esatta, usa il primo server per quella porta
	for(int i = 1; i <= n_server; i++)
	{
		if ((atoi((*configs)[i]->getPort().c_str())) == request_port)
		{
			std::cout << YELLOW "Using default server for port " << request_port << ": " << (*configs)[i]->getServer_name() << END << std::endl;
			return (*configs)[i];
		}
	}

	return NULL;
}

int client_request(std::vector<pollfd> *pollfds, Request *request, std::map<int, Config*> *configs, size_t *i, std::vector<Request> *requests, int n_server)
{
	char temp_buffer[8192];
	int	bytes_read = 0;

	//lettura dell'header
	if (request->checkHead())
	{
		bytes_read = recv((*pollfds)[*i].fd, temp_buffer, 8192, 0);
		if (bytes_read == 0)
			close_socket(pollfds, requests, i);
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
	memset(temp_buffer, 0, sizeof(temp_buffer));
	//lettura del body se ce n'è bisogno
	if (request->checkBody())
	{
		bytes_read = recv((*pollfds)[*i].fd, temp_buffer, 8192, 0);
		if (bytes_read == 0)
			close_socket(pollfds, requests, i);
		if (bytes_read < 0)
			return 0;
		request->setRequest(temp_buffer, bytes_read);
		if (request->checkBody())
			return 0;
	}
	request->setBodyLength();
	request->setBody();
	std::cout << *request << std::endl;
	std::cout << request->getRequest() << std::endl;
	//controllo il ritorno del recv
	if (bytes_read > 0)
	{
		//ritorno una risposta al sito
		request->response = server_response(request, check_config(configs, request, n_server));
		// send((*pollfds)[*i].fd, response.c_str(), response.length(), 0);
	}
	else if (bytes_read == 0)
		close_socket(pollfds, requests, i);
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
	std::string file_name = argv[1];
	if (file_name.find(".config") == std::string::npos)
	{
		std::cerr << "wrong config_file extention" << std::endl;
		return 1;
	}
	init_signals();
	//dichiarazione per la configurazioe e la request
	int						n_server = get_number_server(argv[1]);
	int						n_socket;
	std::string				port_print = "";
	std::map<int, Config*>	configs;
	std::vector<pollfd>		pollfds;
	std::vector<Request>	requests;
	if (init_config(argv[1], configs, &pollfds, n_server, n_socket)) //inizializzazione del socket per il server
		return 1;
	for (int i = 1; i <= n_server; i++)
	{
		std::cout << MAGENTA "" << *configs[i] << "" END << std::endl;
		port_print = port_print + " " + configs[i]->getServer_name() + ":" + configs[i]->getPort() + ",";
	}
	std::cout << YELLOW "Server listening on port:" << port_print << "\n" END << std::endl;
	//loop per la gestione delle richieste
	// std::cout << RED << exec_perl("srcs/server/map.pl 10 10 4") << END << std::endl;
	try
	{
		while (1) {
			//check del poll per verificare lo stato delle request
			std::cout << YELLOW "===waiting for poll===" END << std::endl;
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
				if (pollfds[i].revents & POLLERR) //errore del poll, errore generico
				{
					close_socket(&pollfds, &requests, &i);
					size = pollfds.size();
					continue;
				}
				if (pollfds[i].revents & POLLHUP) //errore del poll, chiusura delle connessione
				{
					close_socket(&pollfds, &requests, &i);
					size = pollfds.size();
					continue;
				}
				if (pollfds[i].revents & POLLIN) //la request viene letta e gestita
				{
					if (check_server_fd(pollfds[i].fd, n_socket, &pollfds)) //connessione di un nuovo client
					{
						int fd = new_connection(pollfds[i].fd);
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
					{
						if (client_request(&pollfds, &requests[i - n_socket], &configs, &i, &requests, n_server)) //richiesta da un client già connesso
							return 1;
						pollfds[i].events = POLLIN | POLLOUT;
					}
				}
				else if (pollfds[i].revents & POLLOUT)
				{
					if (requests[i - n_socket].response != "")
					{
						ssize_t bytes_sent = send(pollfds[i].fd, requests[i - n_socket].response.c_str(), requests[i - n_socket].response.length(), 0);
						if (bytes_sent > 0)
						{
							requests[i - n_socket].response.erase(0, bytes_sent);
							if (requests[i - n_socket].response.empty())
							{
								pollfds[i].events = POLLIN;
							}
						}
						else {
							std::cerr << RED "Errore nell'invio della risposta: " END << strerror(errno) << std::endl;
							close_socket(&pollfds, &requests, &i);
							size = pollfds.size();
						}
					}
					else
						pollfds[i].events = POLLIN;
				}
				pollfds[i].revents = 0;
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << RED "Server shutting down..." END << std::endl;
		std::cerr << "Exception caught: " << e.what() << std::endl;
	}
	for	(int i = 1; i <= n_server; i++)
		delete configs[i];
	for (size_t i = 0; i < pollfds.size(); ++i)
		close(pollfds[i].fd);
	// requests.clear();
	pollfds.clear();
	// config.clearConf();
	std::cout << GREEN "Server closed" END << std::endl;
	std::cout << YELLOW "=========================Server closed=============================" END << std::endl;
	return 0;
}
