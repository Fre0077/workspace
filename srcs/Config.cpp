/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:14 by fde-sant          #+#    #+#             */
/*   Updated: 2025/09/17 18:08:03 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Config.hpp"
//==============================================================================
//COSTRUCTOR/ESTRUCTOR==========================================================
//==============================================================================
Config::Config() {}

Config::Config(std::string name, int n, std::map<std::string, std::string> cgi) : cgi_types(cgi)
{
	std::ifstream file(name.c_str());
	std::string temp, temp2, temp3;
	std::string line;
	this->max_body_len = 8192;
	this->server_name = "";
	this->root = "";
	this->index = "";
	this->method = 0;
	int graph = 0;
	
	this->file_name = name;
	d_error_pages[400] = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/html\r\nContent-Length: 50\r\nConnection: close\r\n\r\n<html><body><h1>400 Bad request</h1></body></html>";
	d_error_pages[403] = "HTTP/1.1 403 Forbidden\r\nContent-Type: text/html\r\nContent-Length: 48\r\nConnection: close\r\n\r\n<html><body><h1>403 Forbidden</h1></body></html>";
	d_error_pages[404] = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: 53\r\nConnection: close\r\n\r\n<html><body><h1>404 File Not Found</h1></body></html>";
	d_error_pages[405] = "HTTP/1.1 405 Method Not Allowed\r\nContent-Type: text/html\r\nContent-Length: 57\r\nConnection: close\r\n\r\n<html><body><h1>405 Method Not Allowed</h1></body></html>";
	d_error_pages[406] = "HTTP/1.1 406 Not Acceptable\r\nContent-Type: text/html\r\nContent-Length: 53\r\nConnection: close\r\n\r\n<html><body><h1>406 Not Acceptable</h1></body></html>";
	d_error_pages[413] = "HTTP/1.1 413 Payload Too Large\r\nContent-Type: text/html\r\nContent-Length: 56\r\nConnection: close\r\n\r\n<html><body><h1>413 Payload Too Large</h1></body></html>";
	d_error_pages[418] = "HTTP/1.1 418 I'm a teapot\r\nContent-Type: text/html\r\nContent-Length: 51\r\nConnection: close\r\n\r\n<html><body><h1>418 I'm a teapot</h1></body></html>";
	d_error_pages[500] = "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/html\r\nContent-Length: 60\r\nConnection: close\r\n\r\n<html><body><h1>500 Internal Server Error</h1></body></html>";
	d_error_pages[501] = "HTTP/1.1 501 Not Implemented\r\nContent-Type: text/html\r\nContent-Length: 54\r\nConnection: close\r\n\r\n<html><body><h1>501 Not Implemented</h1></body></html>";
	error_pages[400] = "";
	error_pages[403] = "";
	error_pages[404] = "";
	error_pages[405] = "";
	error_pages[406] = "";
	error_pages[413] = "";
	error_pages[418] = "";
	error_pages[501] = "";
	n--;
	while (std::getline(file, line))
	{
		//std::cout << graph  << "    " << n << std::endl;
		if (line.find("}") != std::string::npos)
			graph--;
		if (line.find("{") != std::string::npos)
			graph++;
		if (graph == 0 && line.find("}") != std::string::npos)
			n--;
		if (line == "" || line == "\t" || n != 0)
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
					if (this->locations[temp].method < 8)
						this->locations[temp].method += 8;
					if (line.find("GET") != std::string::npos && (this->method & 1) == 1)
						this->locations[temp].method += 1;
					if (line.find("POST") != std::string::npos && (this->method & 2) == 2)
						this->locations[temp].method += 2;
					if (line.find("DELETE") != std::string::npos && (this->method & 4) == 4)
						this->locations[temp].method += 4;
				}
				else if (line.find("upload_directory") == line.find_first_not_of(" \t"))
				{
					std::istringstream iss(line);
					iss >> temp2 >> temp2;
					removeChar(&temp2, ';');
					removeChar(&temp2, '}');
					this->locations[temp].upload_directory = temp2;
				}
				else if (line.find("return") == line.find_first_not_of(" \t"))
				{
					std::istringstream iss(line);
					iss >> temp2 >> temp2 >> temp3;
					removeChar(&temp3, ';');
					removeChar(&temp3, '}');
					this->locations[temp].redirection = temp2 + " " + temp3;
				}
			}
			std::cout << "location: " << temp << std::endl;
			std::cout << "root: " << this->locations[temp].root << std::endl;
			std::cout << "index: " << this->locations[temp].index << std::endl;
			std::cout << "method: " << this->locations[temp].method << std::endl;
			std::cout << "uplaod: " << this->locations[temp].upload_directory << std::endl;
			std::cout << "redirection: " << this->locations[temp].redirection << std::endl;
			std::cout << "=========================" << std::endl;
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
			else if (temp2 == "406")
				this->error_pages[406] = temp;
			else if (temp2 == "413")
				this->error_pages[413] = temp;
			else if (temp2 == "418")
				this->error_pages[418] = temp;
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
		else if (line.find("index") == line.find_first_not_of(" \t"))
		{
			std::istringstream iss(line);
			iss >> temp >> temp;
			removeChar(&temp, ';');
			this->index = temp;
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
		}
	}
	file.close();
}

Config::Config(Config const& copy)
{
	this->server_name = copy.server_name;
	this->error_pages = copy.error_pages;
	this->port = copy.port;
	this->root = copy.root;
}

Config::~Config()
{
	this->locations.clear();
	this->d_error_pages.clear();
	this->error_pages.clear();
	this->server_name.clear();
	this->file_name.clear();
	this->root.clear();
	this->port.clear();
	std::cout << RED "Config destructor called" END << std::endl;
}
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
	out << "index: " << rhs.getIndex() << std::endl;
	out << "port: " << rhs.getPort() << std::endl;
	out << "root: " << rhs.getRoot() << std::endl;
	out << "######################" END << std::endl;
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
	// return this->locations[location];
	if (this->locations.find(location) == this->locations.end())
		return t_location();
	return this->locations[location];
}

int Config::getLocationMethod(std::string location)
{
	if (this->checkPath(location))
		return -1;
	return this->locations[location].method;
}

std::string Config::getLocationUpload(std::string location)
{
	if (this->checkPath(location))
		return "";
	return this->locations[location].upload_directory;
}

std::string Config::getLocationIndex(std::string location)
{
	if (this->checkPath(location))
		return this->root + "/" + this->index;
	if (this->locations[location].redirection != "")
		if (this->locations.find(this->locations[location].redirection.substr(this->locations[location].redirection.find("/"))) != this->locations.end())
			return this->getLocationRoot(location) + "/" + this->locations[this->locations[location].redirection.substr(this->locations[location].redirection.find("/"))].index;
	return this->getLocationRoot(location) + "/" + this->locations[location].index;
}

std::string Config::getLocationRoot(std::string location)
{
	if (this->checkPath(location))
		return this->root;
	if (this->locations[location].root == "")
		return this->root;
	return this->locations[location].root;
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
	return this->root + "/" + this->index;
}

std::string Config::getRoot() const
{
	return this->root;
}

std::string Config::getPort() const
{
	return this->port;
}

std::map<std::string, std::string> Config::getCgi_types() const
{
	return this->cgi_types;
}

size_t Config::getMax_body_len() const
{
	return this->max_body_len;
}

int Config::getMethod() const
{
	return this->method;
}

void Config::clearConf()
{
	this->locations.clear();
	this->d_error_pages.clear();
	this->error_pages.clear();
	this->server_name.clear();
	this->file_name.clear();
	this->root.clear();
	this->port.clear();
	std::cout << RED "Config clearConf called" END << std::endl;
}

void	Config::setFd(int newfd) {
	this->fd = newfd;
}

int	Config::getFd() {
	return this->fd;
}