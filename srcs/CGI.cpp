/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:35:36 by alborghi          #+#    #+#             */
/*   Updated: 2025/09/16 12:14:37 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/webserv.hpp"

std::string get_status_message(int status) {
	std::map<int, std::string> status_codes;
	status_codes[200] = "OK";
	status_codes[201] = "Created";
	status_codes[202] = "Accepted";
	status_codes[204] = "No Content";
	status_codes[301] = "Moved Permanently";
	status_codes[302] = "Found";
	status_codes[307] = "Temporary Redirect";
	status_codes[308] = "Permanent Redirect";
	status_codes[400] = "Bad Request";
	status_codes[401] = "Unauthorized";
	status_codes[403] = "Forbidden";
	status_codes[404] = "Not Found";
	status_codes[405] = "Method Not Allowed";
	status_codes[406] = "Not Acceptable";
	status_codes[413] = "Payload Too Large";
	status_codes[418] = "I'm a teapot";
	status_codes[500] = "Internal Server Error";
	status_codes[501] = "Not Implemented";
	status_codes[502] = "Bad Gateway";
	status_codes[503] = "Service Unavailable";

	try
	{
		return status_codes.at(status);
	}
	catch (...)
	{
		return "Unknown Status";
	}
}

std::string exec_cgi(std::string cgi_path, Request *request, std::string interpreter)
{
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		std::cerr << "Pipe error: " << strerror(errno) << std::endl;
		return "";
	}

	pid_t pid = fork();
	if (pid == 0)
	{
		close(pipe_fd[0]); // Close unused read end
		std::string directory = cgi_path.substr(0, cgi_path.find_last_of('/'));
		std::string script_name = cgi_path.substr(cgi_path.find_last_of('/') + 1);
		std::cout << "Executing CGI: " << directory << " , " << script_name << ", with interpreter: " << interpreter << std::endl;
		dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe
		close(pipe_fd[1]);

		if (chdir(directory.c_str()) != 0)
		{
			std::cerr << "chdir error: " << strerror(errno) << std::endl;
			exit(1);
		}

		// Create environment variable strings
		std::string script_env = "SCRIPT_NAME=" + script_name;
		std::string method_env = "REQUEST_METHOD=" + request->getMethod();
		std::string path_env = "PATH_INFO=" + cgi_path;
		char *env[] = {(char*)script_env.c_str(), (char*)method_env.c_str(), (char *)path_env.c_str(), NULL};

		if (!interpreter.empty())
		{
			char *args[] = {(char*)interpreter.c_str(), (char*)script_name.c_str(), NULL};
			execve(interpreter.c_str(), args, env);
		}
		else
		{
			char *args[] = {(char*)script_name.c_str(), NULL};
			execve(script_name.c_str(), args, env);
		}
		std::cerr << "Exec error: " << strerror(errno) << std::endl;
		exit(1);
	}
	else if (pid > 0)
	{
		close(pipe_fd[1]);
        waitpid(pid, NULL, 0);
        
        std::string result;
        char buffer[1024];
        ssize_t bytes;
        while ((bytes = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0)
        {
            buffer[bytes] = '\0';
            result += buffer;
        }
        close(pipe_fd[0]);
        return result.substr(result.find("<body>") + 6, result.find("</body>") - (result.find("<body>") + 6));
	}
	return "";
}