/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:46:54 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/07 15:21:24 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_echo_flags(char **args)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	f = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] == ' ')
			j++;
		if (args[i][j] == '-' && args[i][j + 1] == 'n')
		{
			while (args[i][++j] && args[i][j] == 'n')
				j++;
			if (args[i][j - 1] == 'n' && args[i][j] != '\0')
				break;
			f++;
		}
		else
			break ;
		if (args[i][j] == '\0')
			i++;
	}
	return (f);
}

void	exec_echo(char **args)
{
	int		i;
	int		f;

	if (!args)
		return ;
	i = 0;
	f = handle_echo_flags(args);
	if (f != 0)
		i = f;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
		if (args[i])
			printf(" ");
	}
	if (f == 0)
		printf("\n");
}
