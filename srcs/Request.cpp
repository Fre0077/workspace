/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:35:32 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/19 10:39:43 by fde-sant         ###   ########.fr       */
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
	head_length = 0;
	length = 0;
	head_need = TRUE;
	body_need = FALSE;
}

Request::Request(Request const& copy)
{
	this->boundary = copy.boundary;
	this->request = copy.request;
	this->method = copy.method;
	this->path = copy.path;
	this->length = copy.length;
	this->head_need = copy.head_need;
	this->body_need = copy.body_need;
}

Request::~Request() {}
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
int	Request::checkHead()
{
	if (request.find("\r\n\r\n") == std::string::npos)
		this->head_need = TRUE;
	else
		this->head_need = FALSE;
	return this->head_need;
}

int	Request::checkBody()
{
	if (this->method != "POST")
		return FALSE;
	if (request.size() - head_length < length)
		this->body_need = TRUE;
	else
		this->body_need = FALSE;
	return this->body_need;
}

void	Request::clearRequest()
{
	boundary.clear();
	request.clear();
	method.clear();
	path.clear();
	head_length = 0;
	length = 0;
	head_need = TRUE;
	body_need = FALSE;
}

void	Request::setRequest(std::string newPart, int len)
{
	request.append(newPart.c_str(), len);
}

void	Request::setRequestType()
{
	std::istringstream iss(request);
	std::string method, path;
	iss >> this->method >> this->path;
}

void	Request::setHeadLength()
{
	this->head_length = request.find("\r\n\r\n") + 4;
}

void	Request::setBoundary()
{
	size_t first = request.find("Content-Type:");
	if (first == std::string::npos)
	{
		this->boundary = "";
		return ;
	}
	std::string temp;
	
	while (request[first - 1] != '\n')
		first = request.find("Content-Type:");
	temp = request.substr(first);
	first = temp.find("boundary=") + 9;
	size_t second = temp.find("\r\n");
	this->boundary = temp.substr(first, second - first);
}

void	Request::setLength()
{
	std::string line, temp;
	size_t pos = request.find("Content-Length:");
	if (pos == std::string::npos)
	{
		this->length = 0;
		return ;
	}
	line = request.substr(pos);
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

size_t	Request::getHeadLength() const
{
	return (this->head_length);
}

size_t	Request::getLength() const
{
	return this->length;
}