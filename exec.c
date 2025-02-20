/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:33:19 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/20 17:44:34 by alborghi         ###   ########.fr       */
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
			printf("%s\n", env->var);
		env = env->next;
	}
}

int	check_pipe(t_cmd *cmds)
{
	if (!cmds || !cmds->next)
		return (0);
	return (1);
}

//TODO: do check on data->status and if value is -1 exit program with status 1
int	call_function(t_data *data)
{
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
		return (printf("exit\n"), -1);
	else
		exec_execve(data);
	return (0);
}

//TODO: check if there is a way to remove the fork here
//void	exec_cmd(t_data *data)
//{
//	if (check_pipe(data->cmds))
//	{
//		int fd[2];
//		int pid;

//		pipe(fd);
//		pid = fork();
//		if (pid == -1)
//			return ;
//		if (pid == 0)
//		{
//			close(fd[0]);
//			if (dup2(fd[1], 1) == -1)
//				exit(1);
//			close(fd[1]);
//			call_function(data);
//			if (dup2(data->stdo, 1) == -1)
//				exit(1);
//			exit(0);
//		}
//		else
//		{
//			close(fd[1]);
//			if (dup2(fd[0], 0) == -1)
//				exit(1);
//			close(fd[0]);
//			data->cmds = data->cmds->next;
//			exec_cmd(data);
//			if (dup2(data->stdi, 0) == -1)
//				exit(1);
//		}
//	}
//	else
//	{
//		call_function(data);
//	}
//}


void	exec_cmd(t_data *data)
{
	int fd[2];

	if (check_pipe(data->cmds))
	{
		pipe(fd);
		if (dup2(fd[1], 1) == -1)
			exit(1);
		call_function(data);
		if (dup2(data->stdo, 1) == -1)
			exit(1);
		close(fd[1]);
		data->cmds = data->cmds->next;
		if (dup2(fd[0], 0) == -1)
			exit(1);
		close(fd[0]);
		exec_cmd(data);
		if (dup2(data->stdi, 0) == -1)
			exit(1);
	}
	else
		call_function(data);
}