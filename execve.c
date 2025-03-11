/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:23:19 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/11 10:04:48 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_execve(char *exec, char **argv, char **env)
{
	free(exec);
	ft_free_mat_char(argv);
	ft_free_mat_char(env);
}

char	*find_path(char *cmd, char *path)
{
	char	**paths;
	int		i;
	char	*tmp;

	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (ft_free_mat_char(paths), NULL);
		tmp = ft_strjoin_free_1(tmp, cmd);
		if (!tmp)
			return (ft_free_mat_char(paths), NULL);
		if (access(tmp, F_OK | X_OK) == 0)
			return (ft_free_mat_char(paths), tmp);
		free(tmp);
		i++;
	}
	ft_free_mat_char(paths);
	return (NULL);
}

char	**get_args(t_cmd *cmds)
{
	char	**argv;
	int		i;

	argv = (char **)ft_calloc(ft_char_mat_len(cmds->args) + 2, sizeof(char *));
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup(cmds->cmd);
	i = 0;
	while (cmds->args && cmds->args[i])
	{
		argv[i + 1] = ft_strdup(cmds->args[i]);
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
		mat[i] = ft_strdup(tmp->var);
		i++;
		tmp = tmp->next;
	}
	mat[i] = NULL;
	return (mat);
}

void	ft_put_char_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
	{
		printf("%s\n", mat[i]);
		i++;
	}
}

// + 128 to get the signal number
int	execute_command(char *path, char **argv, char **env)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == -1)
	return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		execve(path, argv, env);
		perror("execve");
		ft_exit(NULL, 1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free_execve(path, argv, env);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (1);
	}
	return (0);
}

// TODO: add check to argv and env 
int	exec_execve(t_data *data)
{
	char	*path;
	char	*exec;
	char	**argv;
	char	**env;

	if (!data->cmds->cmd || strncmp(data->cmds->cmd, "", 1) == 0)
		return (printf("execve: command not found: %s\n", data->cmds->cmd), 1);
	argv = get_args(data->cmds);
	env = env_to_mat(data->env);
	if (strncmp(data->cmds->cmd, "./", 2) == 0
		|| strncmp(data->cmds->cmd, "/", 1) == 0)
	{
		printf("execve: %s\n", data->cmds->cmd);
		exec = ft_strdup(data->cmds->cmd);
		if (!exec || execute_command(exec, argv, env) == -1)
			return (printf("exec error!\n"), free_execve(exec, argv, env), 1);
		return (0);
	}
	path = get_env(data->env, "PATH");
	exec = find_path(data->cmds->cmd, path);
	if (!exec)
		return (ft_printf("minishell: %s: No such file or directory\n",
				data->cmds->cmd), 127);
	// if (execute_command(exec, argv, env) != 0)
	// 	return (printf("exec error!\n"), free_execve(exec, argv, env), 1);
	// return (0);
	return (execute_command(exec, argv, env));
}
