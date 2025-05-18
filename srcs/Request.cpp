/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:35:32 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/18 12:04:28 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Request.hpp"
//==============================================================================
//COSTRUCTOR/ESTRUCTOR==========================================================
//==============================================================================
Request::Request()
{
	boundary = "";
	request = "";
	method = "";
	path = "";
	length = 0;
}

Request::Request(Request const& copy)
{
	this->boundary = copy.boundary;
	this->request = copy.request;
	this->method = copy.method;
	this->path = copy.path;
	this->length = copy.length;
}
//==============================================================================
//OPERATOR======================================================================
//==============================================================================
Request&	Request::operator=(Request const &copy)
{
	if (this != &copy)
		*this = copy;
	return *this;
}

std::ostream& operator<<(std::ostream& out, Request const& rhs)
{
	out << PURPLE MAGENTA "###REQUEST FILE DATA###" << std::endl;
	out << "boundary: " << rhs.getBoundary() << std::endl;
	out << "method: " << rhs.getMethod() << std::endl;
	out << "path: " << rhs.getPath() << std::endl;
	out << "length: " << rhs.getLength() << std::endl;
	out << "#####################" END << std::endl;
	return out;
}
//==============================================================================
//METHOD========================================================================
//==============================================================================
void	Request::setRequest(std::string newPart)
{
	request.append(newPart);
}

void	Request::setRequestType(std::string name)
{
	std::istringstream iss(name);
	std::string method, path;
	iss >> this->method >> this->path;
}

void	Request::setBoundary(std::string name)
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

void	Request::setLength(std::string name)
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

std::string	Request::getBoundary() const
{
	return this->boundary;
}

std::string	Request::getRequest() const
{
	return this->request;
}

std::string	Request::getMethod() const
{
	return this->method;
}

std::string	Request::getPath() const
{
	return this->path;
}

size_t	Request::getLength() const
{
	return (this->length + 3);
}