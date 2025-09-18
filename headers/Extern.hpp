/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Extern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:39 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/19 18:51:39 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERN_HPP
# define EXTERN_HPP

# include <iostream>
# include <cstdlib>
# include <fstream>
# include <string>
# include <cstring>
# include <sstream>
# include <cerrno>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/select.h>
# include <poll.h>
# include <sys/epoll.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <vector>
# include <map>

// bool
# define TRUE 1
# define FALSE 0

// config methods
# define GET 1
# define POST 2
# define DELETE 4

void	removeChar(std::string *str, char ch);
size_t	stringToSizet(const std::string& str);
int		stringToInt(const std::string& str);

#endif