/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:14 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/19 22:43:29 by fre007           ###   ########.fr       */
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
	this->max_body_len = 0;
	this->port = "4243";
	this->server_name = "";
	this->root = "";
	this->method = 0;
	int graph = 0;
	
	this->file_name = name;
	d_error_pages[400] = "HTTP/1.1 400 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>400 Bad request Bad Request</h1></body></html>";
	d_error_pages[403] = "HTTP/1.1 403 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>403 Forbidden</h1></body></html>";
	d_error_pages[404] = "HTTP/1.1 404 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>404 File Not Found</h1></body></html>";
	d_error_pages[405] = "HTTP/1.1 405 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>405 Method Not Allowed</h1></body></html>";
	d_error_pages[413] = "HTTP/1.1 413 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>413 Payload Too Large</h1></body></html>";
	d_error_pages[500] = "HTTP/1.1 500 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>500 Internal Server Error</h1></body></html>";
	d_error_pages[501] = "HTTP/1.1 501 OK\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: keep-alive\r\n\r\n<html><body><h1>501 Not Implemented</h1></body></html>";
	error_pages[400] = "";
	error_pages[403] = "";
	error_pages[404] = "";
	error_pages[405] = "";
	error_pages[413] = "";
	error_pages[501] = "";
	while (std::getline(file, line))
	{
		if (line.find("{") != std::string::npos)
			graph++;
		if (line.find("}") != std::string::npos)
			graph--;
		if (line == "" || line == "\t")
			continue;
		if (line.find("location") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp;
			removeChar(&temp, '{');
			this->locations[temp];
			while (std::getline(file, line))
			{
				if (line.find("{") != std::string::npos)
					graph++;
				if (line.find("}") != std::string::npos)
					graph--;
				if (graph < 2)
					break;
				if (line.find("root") == line.find_first_not_of(" \t"))
				{
					std::istringstream iss(line);
					iss >> temp2 >> temp2;
					removeChar(&temp2, ';');
					removeChar(&temp2, '}');
					this->locations[temp].root = temp2;
				}
				else if (line.find("index") == line.find_first_not_of(" \t"))
				{
					std::istringstream iss(line);
					iss >> temp2 >> temp2;
					removeChar(&temp2, ';');
					removeChar(&temp2, '}');
					this->locations[temp].index = temp2;
				}
				else if (line.find("method") == line.find_first_not_of(" \t"))
				{
					if (line.find("GET") != std::string::npos)
						this->locations[temp].method += 1;
					if (line.find("POST") != std::string::npos)
						this->locations[temp].method += 2;
					if (line.find("DELETE") != std::string::npos)
						this->locations[temp].method += 4;
				}
			}
		}
		if (graph != 1)
			continue;
		if (line.find("server_name") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->server_name = temp;
		}
		else if (line.find("error_page") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp2 >> temp;
			removeChar(&temp, ';');
			if (temp2 == "400")
				this->error_pages[400] = temp;
			else if (temp2 == "403")
				this->error_pages[403] = temp;
			else if (temp2 == "404")
				this->error_pages[404] = temp;
			else if (temp2 == "405")
				this->error_pages[405] = temp;
			else if (temp2 == "413")
				this->error_pages[413] = temp;
			else if (temp2 == "501")
				this->error_pages[501] = temp;
		}
		else if (line.find("port") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->port = temp;
		}
		else if (line.find("root") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->root = temp;
		}
		else if (line.find("body_size") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->max_body_len = stringToInt(temp);
		}
		else if (line.find("method") == line.find_first_not_of(" \t"))
		{
			if (line.find("GET") != std::string::npos)
				this->method += 1;
			if (line.find("POST") != std::string::npos)
				this->method += 2;
			if (line.find("DELETE") != std::string::npos)
				this->method += 4;
			std::cout << "method: " << this->method << std::endl;
		}
	}
}

Config::Config(Config const& copy)
{
	this->server_name = copy.server_name;
	this->error_pages = copy.error_pages;
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
	out << "max body len: " << rhs.getMax_body_len() << std::endl;
	out << "server name: " << rhs.getServer_name() << std::endl;
	out << "file name: " << rhs.getFile_name() << std::endl;
	out << "method: " << rhs.getMethod() << std::endl;
	out << "port: " << rhs.getPort() << std::endl;
	out << "root: " << rhs.getRoot() << std::endl;
	out << "#####################" END << std::endl;
	return out;
}
//==============================================================================
//METHOD========================================================================
//==============================================================================
int	Config::checkPath(std::string path)
{
	if (this->locations.find(path) == this->locations.end())
		return 1;
	return 0;
}

t_location Config::getLocation(std::string location)
{
	return this->locations[location];
}

int Config::getLocationMethod(std::string location)
{
	return this->locations[location].method;
}

std::string Config::getLocationRoot(std::string location)
{
	if (this->locations[location].root == "")
		return this->root;
	return this->root;
}

std::string Config::getLocationIndex(std::string location)
{
	return this->getLocationRoot(location) + "/" + this->locations[location].index;
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

std::string Config::getRoot() const
{
	return this->root;
}

std::string Config::getPort() const
{
	return this->port;
}

size_t Config::getMax_body_len() const
{
	return this->max_body_len;
}

int Config::getMethod() const
{
	return this->method;
}
