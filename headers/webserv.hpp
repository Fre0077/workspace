/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:26 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/21 14:57:31 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Extern.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "colours.hpp"

int			init_server_socket(int *server_fd, Config config);
int			get_number_server(std::string file_name);
int			init_config(std::string file_name, std::map<int, Config*> &configs, std::vector<pollfd> *pollfds, int n_server);
std::string	server_response(Request *request, Config *config);

#endif