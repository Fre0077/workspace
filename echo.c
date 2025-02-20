/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:46:54 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/20 15:59:26 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * questo dovrebbe essere gestito
 * alborghi@c1r6p7:~$ echo -n dj
 * djalborghi@c1r6p7:~$ echo -nnnnnnnnnnnnnnnnnn dj
 * djalborghi@c1r6p7:~$ echo -nnnnnnnnnnnnnnnnnn -nnn -n  dj
 * djalborghi@c1r6p7:~$ echo -nnnnnnnnnnnnnnnnnn -nngn -n  dj
 * -nngn -n djalborghi@c1r6p7:~$ echo -nnnnnnnnnnnnnnnnnn nnn -n  dj
 * nnn -n djalborghi@c
 */
int	handle_echo_flags(char **args)
{
	int	i;
	int	j;
	int	f;

	i = 0;
	f = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
			f++;
		else
			break ;
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
