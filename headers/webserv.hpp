/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:39:26 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/20 18:11:08 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "Extern.hpp"
# include "Config.hpp"
# include "Request.hpp"
# include "colours.hpp"

int	init_server_socket(int *server_fd, Config config);
std::vector<Config>	createConfig(std::string file_name);
std::string server_response(Request *request, Config *config);

#endif