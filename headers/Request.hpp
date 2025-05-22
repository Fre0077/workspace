/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 11:34:33 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/22 19:35:34 by fre007           ###   ########.fr       */
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
		std::string file_name;
		std::string boundary;
		std::string request;
		std::string method;
		std::string path;
		std::string host;
		std::string body;
		size_t		head_length;
		size_t		body_length;
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
		int			checkPathFile();
		void		clearRequest();
		void		setRequest(const char* newPart, int len);
		void		setRequestType();
		void		setHeadLength();
		void		setBodyLength();
		void		setBoundary();
		void		setLength();
		void		setBody();
		std::string	getDeleteFile() const;
		std::string	getFileName() const;
		std::string	getBoundary() const;
		std::string	getRequest() const;
		std::string	getMethod() const;
		std::string	getPath() const;
		std::string getHost() const;
		std::string getBody() const;
		size_t		getHeadLength() const;
		size_t		getBodyLength() const;
		size_t		getLength() const;
		int			getMethodNum() const;
};

std::ostream& operator<<(std::ostream& out, Request const& rhs);

#endif