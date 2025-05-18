/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:34:33 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/18 12:01:43 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Extern.hpp"
# include "colours.hpp"

class Request
{
private:
	std::string boundary;
	std::string request;
	std::string method;
	std::string path;
	size_t		length;

public:
	Request();
	Request(Request const &copy);
	~Request();
	Request& operator=(Request const &copy);

	void		setRequest(std::string newPart);
	void		setRequestType(std::string name);
	void		setBoundary(std::string name);
	void		setLength(std::string name);
	std::string	getBoundary() const;
	std::string	getRequest() const;
	std::string	getMethod() const;
	std::string	getPath() const;
	size_t		getLength() const;
};

std::ostream& operator<<(std::ostream& out, Request const& rhs);

#endif