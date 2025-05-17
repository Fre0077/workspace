/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/17 20:30:23 by fde-sant         ###   ########.fr       */
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
	//general data
	std::map<int, std::string> d_error_pages;
	std::map<int, std::string> error_pages;
	std::string	server_name;
	std::string	file_name;
	std::string index;
	std::string root;
	std::string port;
	//upload data
	std::string boundary;
	size_t		length;
	int			push_need;

public:
	Config(std::string);
	Config(Config const &copy);
	~Config();
	Config& operator=(Config const &copy);
	//general function
	void		checkConfig();
	std::string searchPathI(std::string location);
	std::string searchPathR(std::string location);
	std::string getDError_page(int i);
	std::string getError_page(int i);
	std::string getServer_name() const;
	std::string getFile_name() const;
	std::string getIndex() const;
	std::string getRoot() const;
	std::string getPort() const;
	//upload function
	void		changePushNeed();
	int			pushNeed();
	void		setBoundary(std::string name);
	void		setLength(std::string name);
	std::string	getBoundary();
	size_t		getLength();
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif