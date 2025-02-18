/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 09:33:19 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/18 18:44:19 by fre007           ###   ########.fr       */
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
	t_cmd	*tmp;

	tmp = cmds;
	while (tmp)
	{
		if (tmp->cmd == NULL)
			return (0);
		if (ft_strncmp(tmp->cmd, "|", 2) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	call_function(t_data *data)
{
	// char	*const argv[] = {cmds->cmd, cmds->args, NULL};
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
	// do check on data->status and if value is -1 exit program with status 1
	return (0);
}

void	exec_cmd(t_data *data)
{
	if (check_pipe(data->cmds))
	{
		printf("handle pipe\n");
	}
	else
	{
		printf("-----output-----\n");
		call_function(data);
	}
}