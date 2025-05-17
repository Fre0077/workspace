/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:01:15 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/17 18:30:58 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "colours.hpp"
# include "Extern.hpp"
# include "Config.hpp"

typedef struct s_red
{
	std::string path;
	std::string file;
}	t_red;

class Server
{
	private:
		Config	config;
		std::vector<t_red> redirects;
	public:
		Server();
		~Server();
};

#endif