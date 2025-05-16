/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Confing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:14 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/16 10:27:11 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"
//==============================================================================
//COSTRUCTOR/ESTRUCTOR==========================================================
//==============================================================================
Config::Config()
{
	this->server_name = "";
	this->error_page = "";
	this->index = "";
	this->port = "";
	this->root = "";
}

Config::Config(std::string)
{
	std::ifstream file("config.txt");
	std::string line;
	while (std::getline(file, line)) {
		
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
