/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:01:15 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/16 12:43:23 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "colours.hpp"
# include "extern.hpp"
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