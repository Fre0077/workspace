/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:02:39 by alborghi          #+#    #+#             */
/*   Updated: 2025/05/16 15:17:49 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTERN_HPP
# define EXTERN_HPP

# include <iostream>			// C++ I/O (cout, cerr)
# include <fstream>
# include <string>			// C++ string
# include <cstring>			// C string
# include <sstream>
# include <cerrno>			// errno
# include <unistd.h>       // execve, pipe, dup, dup2, fork, close, read, write, chdir, access
# include <sys/types.h>    // Required for many system calls
# include <sys/socket.h>   // socket, accept, listen, send, recv, bind, connect, setsockopt, getsockname, socketpair
# include <netdb.h>        // getaddrinfo, freeaddrinfo, gai_strerror, getprotobyname
# include <arpa/inet.h>    // htons, htonl, ntohs, ntohl
# include <sys/select.h>   // select
# include <poll.h>         // poll
# include <sys/epoll.h>    // epoll (Linux only)
# include <fcntl.h>        // fcntl, open
# include <sys/wait.h>     // waitpid
# include <signal.h>       // kill, signal
# include <sys/stat.h>     // stat
# include <dirent.h>       // opendir, readdir, closedir
# include <vector>			// std::vector

void removeChar(std::string *str, char ch);

#endif