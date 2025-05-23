/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:35:32 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/22 19:56:35 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Request.hpp"
//==============================================================================
//COSTRUCTOR/ESTRUCTOR==========================================================
//==============================================================================
Request::Request()
{
	delete_file = "";
	file_name = "";
	boundary = "";
	request = "";
	method = "";
	path = "";
	host = "";
	body = "";
	head_length = 0;
	body_length = 0;
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
	{
		this->boundary = copy.boundary;
		this->request = copy.request;
		this->method = copy.method;
		this->path = copy.path;
		this->length = copy.length;
		this->head_length = copy.head_length;
		this->body_length = copy.body_length;
		this->head_need = copy.head_need;
		this->body_need = copy.body_need;
		this->delete_file = copy.delete_file;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, Request const& rhs)
{
	out << PURPLE MAGENTA "###REQUEST FILE DATA###" << std::endl;
	out << "delete file: " << rhs.getDeleteFile() << std::endl;
	out << "boundary: " << rhs.getBoundary() << std::endl;
	out << "method: " << rhs.getMethod() << std::endl;
	out << "path: " << rhs.getPath() << std::endl;
	out << "host: " << rhs.getHost() << std::endl;
	out << "length: " << rhs.getLength() << std::endl;
	out << "head length: " << rhs.getHeadLength() << std::endl;
	out << "body length: " << rhs.getBodyLength() << std::endl;
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

int	Request::checkPathFile()
{
	std::string temp = "." + path;
	std::ifstream file(temp.c_str(), std::ios::binary);
	if (!file.is_open())
	{
		file.close();
		return 1;
	}
	file.close();
	return 0;
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

void	Request::setRequest(const char* newPart, int len)
{
	request.append(newPart, len);
}

void	Request::setRequestType()
{
	std::string temp;
	int			pos;
	std::istringstream iss(request);
	iss >> this->method >> this->path >> temp >> temp >> temp;
	if (this->method == "DELETE")
	{
		this->delete_file = this->path;
		this->path = "/delete";
	}
	pos = temp.find(":");
	this->host = temp.substr(pos + 1);
}

void	Request::setHeadLength()
{
	if (request.find("\r\n\r\n") != std::string::npos)
		this->head_length = request.find("\r\n\r\n") + 4;
}

void	Request::setBodyLength()
{
	this->body_length = request.size() - head_length;
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
	first = temp.find("boundary=");
	if (first == std::string::npos)
	{
		this->boundary = "";
		return ;
	}
	first += 9;
	size_t second = temp.find("\r\n");
	this->boundary = temp.substr(first, second - first);
	this->boundary = "--" + this->boundary;
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

void	Request::setBody()
{
	if (this->boundary == "")
		return ;
	std::string request_body = request.substr(request.find(boundary) + boundary.length() + 1);
	std::string file = request_body.substr(0, request_body.find("\r\n"));
	file = file.substr(file.find("filename=\"") + 10);
	this->file_name = "/up_" + file.substr(0, file.find("\""));
	std::string file_data = request_body.substr(request_body.find("\r\n\r\n") + 4);
	this->body = file_data.substr(0, file_data.find("\r\n" + boundary));
}

std::string	Request::getDeleteFile() const
{
	return this->delete_file;
}

std::string	Request::getFileName() const
{
	return this->file_name;
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

std::string	Request::getHost() const
{
	return this->host;
}

std::string	Request::getBody() const
{
	return this->body;
}

size_t	Request::getBodyLength() const
{
	return (this->body_length);
}

size_t	Request::getHeadLength() const
{
	return (this->head_length);
}

size_t	Request::getLength() const
{
	return this->length;
}

int	Request::getMethodNum() const
{
	if (this->method == "GET")
		return 1;
	if (this->method == "POST")
		return 2;
	if (this->method == "DELETE")
		return 4;
	return 0;
}