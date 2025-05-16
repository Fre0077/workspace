/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:14 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 15:42:59 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Config.hpp"
//==============================================================================
//COSTRUCTOR/ESTRUCTOR==========================================================
//==============================================================================
Config::Config()
{
	this->server_name = "";
	this->error_page = "";
	this->file_name = "";
	this->index = "";
	this->port = "";
	this->root = "";
}

Config::Config(std::string name)
{
	this->file_name = name;
	std::string temp;
	int graph = 0;
	std::ifstream file(name.c_str());
	std::string line;
	while (std::getline(file, line))
	{
		//std::cout << line << std::endl;
		//std::cout << graph << std::endl;
		if ((line.find("{") != std::string::npos || graph) && line.find("server") == std::string::npos)
		{
			graph = 1;
			if (line.find("}") != std::string::npos)
				graph = 0;
			continue;
		}
		if (line == "")
			continue;
		if (line.find("server_name") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			std::string method, path, version;
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->server_name = temp;
		}
		else if (line.find("error_page") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			std::string method, path, version;
			iss >> temp >> temp >> temp;
			removeChar(&temp, ';');
			this->error_page = temp;
		}
		else if (line.find("index") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			std::string method, path, version;
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->index = temp;
		}
		else if (line.find("port") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			std::string method, path, version;
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->port = temp;
		}
		else if (line.find("root") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			std::string method, path, version;
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->root = temp;
		}
	}
}

Config::Config(Config const& copy)
{
	this->server_name = copy.server_name;
	this->error_page = copy.error_page;
	this->index = copy.index;
	this->port = copy.port;
	this->root = copy.root;
}

Config::~Config() {}
//==============================================================================
//OPERATOR======================================================================
//==============================================================================
Config&	Config::operator=(Config const &copy)
{
	if (this != &copy)
		*this = copy;
	return *this;
}

std::ostream& operator<<(std::ostream& out, Config const& rhs)
{
	out << "###CONFIG FILE DATA###" << std::endl;
	out << "file name: " << rhs.getFile_name() << std::endl;
	out << "server name: " << rhs.getServer_name() << std::endl;
	out << "error page: " << rhs.getError_page() << std::endl;
	out << "index: " << rhs.getIndex() << std::endl;
	out << "port: " << rhs.getPort() << std::endl;
	out << "root: " << rhs.getRoot() << std::endl;
	return out;
}
//==============================================================================
//METHOD========================================================================
//==============================================================================
std::string Config::searchPath(std::string location)
{
	std::string temp, temp2, name = this->file_name;
	std::ifstream file(name.c_str());
	std::string line;
	while (std::getline(file, line))
	{
		if (line.find("location") == line.find_first_not_of(" \t"))
		{
			std::size_t pos = line.find(location.c_str());
			if (pos != std::string::npos && line[pos + location.length()] == ' ')
			{
				while (std::getline(file, line))
				{
					std::istringstream iss(line);
					std::string method, path, version;
					iss >> temp >> temp2;
					removeChar(&temp2, ';');
					if (temp == "index")
						return (this->root + "/" + temp2);
				}
			}
		}
	}
	return "";
}

std::string Config::getServer_name() const
{
	return this->server_name;
}

std::string Config::getError_page() const
{
	return this->error_page;
}

std::string Config::getIndex() const
{
	return this->index;
}

std::string Config::getRoot() const
{
	return this->root;
}

std::string Config::getPort() const
{
	return this->port;
}

std::string Config::getFile_name() const
{
	return this->file_name;
}
