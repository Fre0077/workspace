/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/22 19:51:24 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Extern.hpp"
# include "colours.hpp"

typedef struct s_location
{
	std::string root;
	std::string index;
	std::string upload_directory;
	int 	method;
}	t_location;

class Config
{
	private:
		std::map<std::string, t_location > locations;
		std::map<int, std::string> d_error_pages;
		std::map<int, std::string> error_pages;
		std::string	server_name;
		std::string	file_name;
		std::string	index;
		std::string root;
		std::string port;
		size_t		max_body_len;
		int			method;
		
	public:
		Config();
		Config(std::string name, int n);
		Config(Config const &copy);
		~Config();
		Config& operator=(Config const &copy);

		int			checkPath(std::string path);
		t_location	getLocation(std::string location);
		int			getLocationMethod(std::string location);
		std::string getLocationUpload(std::string location);
		std::string getLocationIndex(std::string location);
		std::string getLocationRoot(std::string location);
		std::string getDError_page(int i);
		std::string getError_page(int i);
		std::string getServer_name() const;
		std::string getFile_name() const;
		std::string getIndex() const;
		std::string getRoot() const;
		std::string getPort() const;
		size_t 		getMax_body_len() const;
		int 		getMethod() const;
		void		clearConf();
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif