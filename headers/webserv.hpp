/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:26 by alborghi          #+#    #+#             */
/*   Updated: 2025/09/15 17:36:38 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Extern.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "colours.hpp"

int			get_number_server(std::string file_name);
int			init_config(std::string file_name, std::map<int, Config*> &configs, std::vector<pollfd> *pollfds, int n_server);
std::string	server_response(Request *request, Config *config);

std::string exec_perl(std::string cgi_path);
std::string exec_py(std::string cgi_path);

#endif