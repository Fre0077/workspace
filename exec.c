/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:33:19 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/03 17:58:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_env(t_env *env, int is_env)
{
	if (!env)
		return ;
	while (env)
	{
		if (!(is_env == TRUE && env->is_env == FALSE))
			ft_printf("%s\n", env->var);
		env = env->next;
	}
}

int	check_pipe(t_cmd *cmds)
{
	if (!cmds || !cmds->next)
		return (0);
	return (1);
}

// 0644 = rw-r--r-- (user: read, write; group: read; others: read)
int	dup_file(char *file, int std, int mode)
{
	int fd;

	fd = open(file, mode, 0644);
	if (fd == -1)
		return (-1);
	if (dup2(fd, std) == -1)
		return (-1);
	close(fd);
	free(file);
	return (0);
}

int	open_last(char **file, int doi)
{
	int fd;
	int i;

	if (!file || !file[0])
		return (-1);
	i = 0;
	while (file[i + 1])
	{
		fd = open(file[i], O_RDONLY);
		if (fd == -1)
			return (-1);
		close(fd);
		i++;
	}
	fd = open(file[i], O_RDONLY);
	if (fd == -1)
		return (-1);
	if (doi != 1)
		return (close(fd), 0);
	if (dup_file(ft_strdup(file[i]), 0, O_RDONLY) == -1)
		return (-1);
	close(fd);
	return (0);
}

void	handle_delimiter(char **delimiter, int doi, t_data *data)
{
	char	*line;
	int		fd[2];
	int		i;
	int		j;

	if (!delimiter || !delimiter[0])
		return ;
	i = 0;
	j = 0;
	while (delimiter[i + 1])
	{
		line = readline("> ");
		if (!line || !line[0])
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", j, delimiter[i]);
			j = 1;
			i++;
			continue ;
		}
		if (ft_strncmp(line, delimiter[i], ft_strlen(delimiter[i])) == 0)
		{
			i++;
			j = 1;
		}
		free(line);
		j++;
	}
	pipe(fd);
	j = 1;
	while (1)
	{
		line = readline("> ");
		if (!line || !line[0])
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted `%s')\n", j, delimiter[i]);
			break ;
		}
		if (ft_strncmp(line, delimiter[i], ft_strlen(delimiter[i]) + 1) == 0)
		{
			free(line);
			break ;
		}
		//TODO: add dollar managment
		line = dollar_manager_stupid(line, data);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
		j++;
	}
	close(fd[1]);
	if (doi == 2 && dup2(fd[0], 0) == -1)
	{
		close(fd[0]);
		return ;
	}
	close(fd[0]);
}

int	handle_files(t_cmd *cmd, t_data *data)
{
	handle_delimiter(cmd->delimiter, cmd->doi, data);
	if (cmd->file_i)
	{
		if (open_last(cmd->file_i, cmd->doi) == -1)
			return (ft_printf("minishell: No such file or directory"), -1);
	}
	if (cmd->file_o)
	{
		if (dup_file(cmd->file_o, 1, O_CREAT | O_WRONLY | O_TRUNC) == -1)
			return (-1);
	}
	else if (cmd->file_a)
	{
		if (dup_file(cmd->file_a, 1, O_CREAT | O_WRONLY | O_APPEND) == -1)
			return (-1);
	}
	if (cmd->file_i)
		ft_free_mat_char(cmd->file_i);
	ft_free_mat_char(cmd->delimiter);
	return (0);
}

int	reset_std(t_data *data)
{
	if (dup2(data->stdi, 0) == -1)
		return (-1);
	if (dup2(data->stdo, 1) == -1)
		return (-1);
	return (0);
}

//TODO: do check on data->status and if value is -1 exit program with status 1
//TODO: add a function to handle <, >, >>, <<
//										   << is the same as here_doc in pipex
int	call_function(t_data *data)
{
	if (handle_files(data->cmds, data) == -1)
		return (-1);
	if (ft_strncmp(data->cmds->cmd, "echo", 5) == 0)
		exec_echo(data->cmds->args);
	else if (ft_strncmp(data->cmds->cmd, "cd", 3) == 0)
		exec_cd(data);
	else if (ft_strncmp(data->cmds->cmd, "pwd", 4) == 0)
		printf("%s\n", data->pwd);
	else if (ft_strncmp(data->cmds->cmd, "export", 7) == 0)
		exec_export(data->cmds, data->env);
	else if (ft_strncmp(data->cmds->cmd, "unset", 6) == 0)
		exec_unset(data);
	else if (ft_strncmp(data->cmds->cmd, "env", 4) == 0)
		ft_put_env(data->env, TRUE);
	else if (ft_strncmp(data->cmds->cmd, "exit", 5) == 0)
		return (printf("exit\n"), data->status = 1, -1);
	else
		exec_execve(data);
	// free_cmds(data->cmds);
	// reset_std(data);
	return (0);
}

int is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	check_cmds(t_cmd *cmds, t_env *env)
{
	char	*path;
	char	*exec;
	t_cmd	*tmp;

	path = get_env(env, "PATH");
	if (!path)
		return (printf("command not found: %s\n", cmds->cmd), 1);
	tmp = cmds;
	while (tmp)
	{
		if (is_builtin(tmp->cmd) == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		exec = find_path(tmp->cmd, path);
		if (!exec)
			return (printf("command not found: %s\n", tmp->cmd), 1);
		tmp = tmp->next;
		free(exec);
	}
	return (0);
}

void	exec_cmd(t_data *data)
{
	int fd[2];
	int pid;

	if (check_cmds(data->cmds, data->env) == 1)
		return ;
	if (check_pipe(data->cmds))
	{
		if (pipe(fd) == -1)
			return (perror("pipe"));
		pid = fork();
		if (pid == -1)
			return (perror("fork"));
		if (pid == 0)
		{
			close(fd[0]);
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				close(fd[1]);
				ft_exit(data);
			}
			close(fd[1]);
			call_function(data);
			close(STDOUT_FILENO);
			ft_exit(data);
		}
		else
		{
			close(fd[1]);
			if (dup2(fd[0], STDIN_FILENO) == -1)
			{
				close(fd[0]);
				ft_exit(data);
			}
			close(fd[0]);
			data->cmds = data->cmds->next;
			exec_cmd(data);
			waitpid(pid, NULL, 0);
		}
	}
	else
	{
		call_function(data);
		reset_std(data);
	}
}
