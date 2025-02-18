/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:23:19 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/18 18:24:05 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char *path)
{
	char	**paths;
	int		i;
	char	*tmp;

	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		tmp = ft_strjoin_free_1(tmp, cmd);
		if (!tmp)
			return (NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	**get_args(t_cmd *cmds)
{
	char	**argv;
	int		i;

	argv = (char **)ft_calloc(ft_char_mat_len(cmds->args) + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = cmds->cmd;
	i = 0;
	while (cmds->args && cmds->args[i])
	{
		argv[i + 1] = cmds->args[i];
		i++;
	}
	argv[i + 1] = NULL;
	return (argv); 
}

char	**env_to_mat(t_env *env)
{
	char	**mat;
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	mat = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!mat)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		mat[i] = tmp->var;
		i++;
		tmp = tmp->next;
	}
	mat[i] = NULL;
	return (mat);
}

int execute_command(char *path, char **argv, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
        return (perror("fork"), 1);
	if (pid == 0)
	{
		execve(path, argv, env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128); // + 128 to get the signal number
		return (1);
	}
	return (0);
}

int	exec_execve(t_data *data)
{
	char	*path;
	char	*exec;
	char	**argv;
	char	**env;

	path = get_env(data->env, "PATH");
	if (!path)
		return (1);
	path += 1;
	exec = find_path(data->cmds->cmd, path);
	argv = get_args(data->cmds);
	env = env_to_mat(data->env);
	if (execute_command(exec, argv, env) == -1)
		return (printf("exec error!\n"), 1);
	return (0);
}
