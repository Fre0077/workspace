/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:26 by alborghi          #+#    #+#             */
/*   Updated: 2025/09/16 12:10:38 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Extern.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "colours.hpp"

#include <set>

int			get_number_server(std::string file_name);
int			init_config(std::string file_name, std::map<int, Config*> &configs, std::vector<pollfd> *pollfds, int n_server);
std::string	server_response(Request *request, Config *config);

std::string exec_cgi(std::string cgi_path, Request *request, std::string interpreter = "");
std::map<std::string, std::string> init_cgi_types();

std::string get_status_message(int status);

#endif