/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:13 by fre007            #+#    #+#             */
/*   Updated: 2025/02/20 16:03:34 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printa tutta al  lista delle parole
void	print_word(t_words *words)
{
	while (words != NULL)
	{
		ft_printf("%s\n", words->word);
		words = words->next;
	}
}

//printa tutta la lista dei comandi
void	print_cmd(t_cmd *cmds)
{
	int	i;

	while (cmds != NULL)
	{
		ft_printf("cmd: %s\n", cmds->cmd);
		i = -1;
		ft_printf("arg: ");
		while (cmds->args[++i] != NULL)
			ft_printf("%s, ", cmds->args[i]);
		ft_printf("%s\n", cmds->args[i]);
		cmds = cmds->next;
	}
}
