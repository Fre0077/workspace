/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:14 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/17 20:35:48 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Config.hpp"
//==============================================================================
//COSTRUCTOR/ESTRUCTOR==========================================================
//==============================================================================
Config::Config(std::string name)
{
	std::ifstream file(name.c_str());
	std::string temp, temp2;
	std::string line;
	int graph = 0;
	
	this->file_name = name;
	d_error_pages[400] = "HTTP/1.1 400 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>400 Bad request Bad Request</h1></body></html>";
	d_error_pages[403] = "HTTP/1.1 403 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>403 Forbidden</h1></body></html>";
	d_error_pages[404] = "HTTP/1.1 404 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>404 File Not Found</h1></body></html>";
	d_error_pages[405] = "HTTP/1.1 405 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>405 Method Not Allowed</h1></body></html>";
	d_error_pages[500] = "HTTP/1.1 500 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>500 Internal Server Error</h1></body></html>";
	d_error_pages[501] = "HTTP/1.1 501 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>501 Not Implemented</h1></body></html>";
	error_pages[400] = "";
	error_pages[403] = "";
	error_pages[404] = "";
	error_pages[405] = "";
	error_pages[501] = "";
	this->boundary = "";
	this->push_need = 0;
	this->length = 0;
	while (std::getline(file, line))
	{
		if (line.find("{") != std::string::npos)
			graph++;
		if (line.find("}") != std::string::npos)
			graph--;
		if (graph != 1 || line == "")
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
			iss >> temp >> temp2 >> temp;
			removeChar(&temp, ';');
			if (temp2 == "400")
				this->error_pages[400] = temp;
			else if (temp2 == "403")
				this->error_pages[403] = temp;
			else if (temp2 == "404")
				this->error_pages[404] = temp;
			else if (temp2 == "405 ")
				this->error_pages[405] = temp;
			else if (temp2 == "501")
				this->error_pages[501] = temp;
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
	this->error_pages = copy.error_pages;
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
	out << PURPLE MAGENTA "###CONFIG FILE DATA###" << std::endl;
	out << "file name: " << rhs.getFile_name() << std::endl;
	out << "server name: " << rhs.getServer_name() << std::endl;
	out << "index: " << rhs.getIndex() << std::endl;
	out << "port: " << rhs.getPort() << std::endl;
	out << "root: " << rhs.getRoot() << std::endl;
	out << "#####################" END << std::endl;
	return out;
}
//==============================================================================
//METHOD========================================================================
//==============================================================================
void	Config::checkConfig()
{
	std::cout << PURPLE MAGENTA "###CONFIG FILE DATA###" << std::endl;
	std::cout << "file name: " << this->getFile_name() << std::endl;
	std::cout << "server name: " << this->getServer_name() << std::endl;
	std::cout << "index: " << this->getIndex() << std::endl;
	std::cout << "port: " << this->getPort() << std::endl;
	std::cout << "root: " << this->getRoot() << std::endl;
	std::cout << "boundary: " << this->getBoundary() << std::endl;
	std::cout << "length: " << this->getLength()<< std::endl;
	std::cout << "#####################" END << std::endl;
}

std::string Config::searchPathI(std::string location)
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
std::string Config::searchPathR(std::string location)
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
					if (temp == "root")
						return temp2;
				}
			}
		}
	}
	return "";
}

std::string Config::getDError_page(int i)
{
	return this->d_error_pages[i];
}

std::string Config::getError_page(int i)
{
	return this->error_pages[i];
}

std::string Config::getServer_name() const
{
	return this->server_name;
}

std::string Config::getFile_name() const
{
	return this->file_name;
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

void	Config::changePushNeed()
{
	if (this->push_need == 0)
	this->push_need = 1;
	else
	this->push_need = 0;
}

int	Config::pushNeed()
{
	return this->push_need;
}

void	Config::setBoundary(std::string name)
{
	size_t first = name.find("Content-Type:");
	if (first == std::string::npos)
	{
		this->boundary = "";
		return ;
	}
	std::string temp;
	
	while (name[first - 1] != '\n')
		first = name.find("Content-Type:");
	temp = name.substr(first);
	first = temp.find("boundary=") + 9;
	size_t second = temp.find("\r\n");
	this->boundary = temp.substr(first, second - first);
}

void	Config::setLength(std::string name)
{
	std::string line, temp;
	size_t pos = name.find("Content-Length:");
	if (pos == std::string::npos)
	{
		this->length = 0;
		return ;
	}
	line = name.substr(pos);
	std::istringstream iss(line);
	iss >> temp >> temp;
	this->length = stringToInt(temp);
}

size_t	Config::getLength()
{
	return (this->length + 3);
}

std::string	Config::getBoundary()
{
	return boundary;
}