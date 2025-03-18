/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:51:57 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/18 09:53:54 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_heredoc(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->cmds)
	{
		if (data->cmds->delimiter && data->cmds->delimiter[0])
		{
			if (skip_useless(data->cmds->delimiter) == -1)
				return (1);
			handle_delimiter(data->cmds->delimiter, 0, data);
			data->cmds->delimiter = NULL;
		}
		data->cmds = data->cmds->next;
	}
	return (0);
}