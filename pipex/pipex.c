/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:14:20 by fde-sant          #+#    #+#             */
/*   Updated: 2025/01/20 10:35:25 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int		j;

	j = -1;
	while (arr[++j])
		free(arr[j]);
}

char	*create_path(char *command, char **env)
{
	int		i;
	char	*path;
	char	**search;
	char	**com;

	i = 0;
	while (confront(env[i], "PATH=", 0, 5) == 0)
		i++;
	path = dupstr(env[i], 5);
	com = ft_split_add(command, NULL, ' ');
	search = ft_split_add(path, com[0], ':');
	i = -1;
	while (search[++i] != NULL)
	{
		if (access(search[i], X_OK) == 0)
		{
			path = dupstr(search[i], 0);
			return (free_arr(com), free_arr(search), path);
		}
	}
	return (NULL);
}

void	process(char *command, char **env)
{
	char	**arg;
	char	*path;

	path = create_path(command, env);
	arg = ft_split_add(command, NULL, ' ');
	if (execve(path, arg, env) == -1)
	{
		free(path);
		free_arr(arg);
		ft_printf("Error\nno process\n");
		exit (EXIT_FAILURE);
	}
	free(path);
	free_arr(arg);
}

int	cicle(char *cmd, char **env)
{
	pid_t	pid;
	int		pip[2];

	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		close(pip[0]);
		if (dup2(pip[1], STDOUT_FILENO) == -1)
			return (ft_printf("Error\nbad dup\n"), 0);
		process(cmd, env);
	}
	else
	{
		close(pip[1]);
		if (dup2(pip[0], STDIN_FILENO) == -1)
			return (ft_printf("Error\nbad dup\n"), 0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	int		i;
	int		fd_out;
	int		fd_in;

	if (ac < 4)
		return (ft_printf("Error\ntoo few arguments\n"), 0);
	fd_in = check_in(av);
	fd_out = check_out(av, ac);
	if (fd_in == -1 || fd_out == -1)
		return (ft_printf("Error\nfile not opened\n"), 0);
	i = 1;
	if (confront(av[1], "here_doc", 0, -1))
		i = 2;
	while (++i < ac - 2)
		if (cicle(av[i], env) == 0)
			return (ft_printf("Error\nbad input dup\n"), 0);
	if (dup2(fd_out, 1) == -1)
		return (ft_printf("Error\nbad output dup\n"), 0);
	process(av[i], env);
	return (0);
}
