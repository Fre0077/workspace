/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 20:15:12 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Extern.hpp"
# include "colours.hpp"

class Config
{
private:
	std::string	server_name;
	std::map<int, std::string> error_pages;
	std::string	file_name;
	std::string index;
	std::string root;
	std::string port;
	
	Config();
public:
	Config(std::string);
	Config(Config const &copy);
	Config& operator=(Config const &copy);
	~Config();
	std::string searchPath(std::string location);
	std::string getServer_name() const;
	std::map<int, std::string> getError_page() const;
	std::string getIndex() const;
	std::string getRoot() const;
	std::string getPort() const;
	std::string getFile_name() const;
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif