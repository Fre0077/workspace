/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Extern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:39 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/16 20:03:39 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERN_HPP
# define EXTERN_HPP

# include <iostream>
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

void	removeChar(std::string *str, char ch);
int		stringToInt(const std::string& str);

#endif