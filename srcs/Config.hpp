/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 09:26:05 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

#include "../headers/webserv.hpp"

class Config
{
private:
	std::string	server_name;
	std::string	error_page;
	std::string index;
	std::string root;
	std::string port;
public:
	Config();
	Config(std::string);
	Config(Config const &copy);
	Config& operator=(Config const &copy);
	~Config();
	std::string searchPath(std::string);
	std::string getServer_name() const;
	std::string getError_page() const;
	std::string getIndex() const;
	std::string getRoot() const;
	std::string getPort() const;
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif