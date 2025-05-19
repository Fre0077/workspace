/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:34:33 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/19 14:42:43 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "Extern.hpp"
# include "colours.hpp"

class Request
{
private:
	std::string delete_file;
	std::string boundary;
	std::string request;
	std::string method;
	std::string path;
	size_t		head_length;
	size_t		length;
	int			head_need;
	int			body_need;

public:
	Request();
	Request(Request const &copy);
	~Request();
	Request& operator=(Request const &copy);

	int			checkHead();
	int			checkBody();
	void		clearRequest();
	void		setRequest(std::string newPart, int len);
	void		setRequestType();
	void		setHeadLength();
	void		setBoundary();
	void		setLength();
	std::string	getDeleteFile() const;
	std::string	getBoundary() const;
	std::string	getRequest() const;
	std::string	getMethod() const;
	std::string	getPath() const;
	size_t		getHeadLength() const;
	size_t		getLength() const;
};

std::ostream& operator<<(std::ostream& out, Request const& rhs);

#endif