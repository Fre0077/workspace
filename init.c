/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:29:44 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/18 10:38:21 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->var);
		free(tmp);
	}
}

t_env	*init_env(char **env)
{
	t_env	*my_env;
	t_env	*tmp;
	int		i;

	if (!env || !*env)
		return (NULL);
	my_env = (t_env *)malloc(sizeof(t_env));
	if (!my_env)
		return (NULL);
	i = 0;
	tmp = my_env;
	while (env[i])
	{
		tmp->var = ft_strdup(env[i]);
		if (!tmp->var)
			return (free_env(my_env), NULL);
		tmp->is_env = TRUE;
		if (env[i++ + 1])
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			if (!tmp->next)
				return (free_env(my_env), NULL);
			tmp = tmp->next;
		}
	}
	tmp->next = NULL;
	return (my_env);
}

int	init_data(t_data *data, char **env)
{
	data->env = init_env(env);
	if (!data->env)
		return (1);
	data->cmds = NULL;
	data->status = 0;
	data->home = ft_strdup(get_env(data->env, "HOME"));
	if (!data->home)
		return (1);
	data->pwd = ft_strdup(get_env(data->env, "PWD"));
	if (!data->pwd)
		return (1);
	data->oldpwd = ft_strdup(get_env(data->env, "OLDPWD"));
	if (!data->oldpwd)
		return (1);
	return (0);
}
