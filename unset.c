/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:22:52 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/06 10:30:32 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (check_arg(key, "unset") == 1)
			return (1);
		if (ft_strncmp(key, "_", 2) == 0)
		{
			i++;
			continue ;
		}
		tmp = data->env;
		last = NULL;
		while (tmp)
		{
			if (strncmp(key, tmp->var, strlen(key)) == 0
				&& (tmp->var[ft_strlen(key)] == '='
				|| tmp->var[ft_strlen(key)] == '\0'))
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
