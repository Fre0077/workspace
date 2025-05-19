/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 08:43:17 by fde-sant          #+#    #+#             */
/*   Updated: 2025/05/19 18:56:01 by alborghi         ###   ########.fr       */
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
	int 	method;
}	t_location;

class Config
{
	private:
		Config();
		std::map<std::string, t_location > locations;
		std::map<int, std::string> d_error_pages;
		std::map<int, std::string> error_pages;
		std::string	server_name;
		std::string	file_name;
		std::string root;
		std::string port;
		int			max_body_len;
		int			method;

	public:
		Config(std::string name);
		Config(Config const &copy);
		~Config();
		Config& operator=(Config const &copy);

		std::string searchPathI(std::string location);
		std::string searchPathR(std::string location);
		t_location	getLocation(std::string location);
		int			getLocationMethod(std::string location);
		std::string getLocationRoot(std::string location);
		std::string getLocationIndex(std::string location);
		std::string getDError_page(int i);
		std::string getError_page(int i);
		std::string getServer_name() const;
		std::string getFile_name() const;
		std::string getRoot() const;
		std::string getPort() const;
		int getMax_body_len() const;
		int getMethod() const;
};

std::ostream& operator<<(std::ostream& out, Config const& rhs);

#endif