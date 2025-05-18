/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/18 11:55:19 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Extern.hpp"
# include "colours.hpp"

class Config
{
private:
	Config();
	std::map<int, std::string> d_error_pages;
	std::map<int, std::string> error_pages;
	std::string	server_name;
	std::string	file_name;
	std::string index;
	std::string root;
	std::string port;

public:
	Config(std::string name);
	Config(Config const &copy);
	~Config();
	Config& operator=(Config const &copy);

	std::string searchPathI(std::string location);
	std::string searchPathR(std::string location);
	std::string getDError_page(int i);
	std::string getError_page(int i);
	std::string getServer_name() const;
	std::string getFile_name() const;
	std::string getIndex() const;
	std::string getRoot() const;
	std::string getPort() const;
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif