/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/18 09:50:25 by fde-sant         ###   ########.fr       */
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
	std::string method;
	std::string path;
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
	void		setRequestType(std::string name);
	void		setBoundary(std::string name);
	void		setLength(std::string name);
	std::string	getBoundary();
	std::string	getMethod();
	std::string	getPath();
	size_t		getLength();
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif