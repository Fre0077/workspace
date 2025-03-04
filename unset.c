/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:22:52 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/28 15:49:56 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_cycle(t_data *data, char *key, t_env **tmp, t_env **last)
{
	if (strncmp(key, (*tmp)->var, strlen(key)) == 0
		&& (*tmp)->var[ft_strlen(key)] == '=')
	{
		if ((*last) == NULL)
			data->env = (*tmp)->next;
		else
			(*last)->next = (*tmp)->next;
		free((*tmp)->var);
		free((*tmp));
		return (1);
	}
	(*last) = (*tmp);
	(*tmp) = (*tmp)->next;
	return (0);
}

int	exec_unset(t_data *data)
{
	t_env	*tmp;
	t_env	*last;
	char	*key;
	int		i;

	if (!data || !data->cmds || !data->cmds->args || !data->cmds->args[0])
		return (1);
	i = 0;
	while (data->cmds->args[i])
	{
		key = data->cmds->args[i];
		if (ft_strncmp(key, "_", 2) == 0)
		{
			i++;
			continue ;
		}
		tmp = data->env;
		last = NULL;
		// while (tmp)
		// 	if (unset_cycle(data, key, &tmp, &last) == 1)
		// 		break ;
		while (tmp)
		{
			if (strncmp(key, tmp->var, strlen(key)) == 0
				&& tmp->var[ft_strlen(key)] == '=')
			{
				if (last == NULL)
					data->env = tmp->next;
				else
					last->next = tmp->next;
				free(tmp->var);
				free(tmp);
				break ;
			}
			last = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}
