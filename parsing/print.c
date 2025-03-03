/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:13 by fre007            #+#    #+#             */
/*   Updated: 2025/03/03 14:53:46 by alborghi         ###   ########.fr       */
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

//printa tutta la struct data
void	print_data(t_data *data)
{
	ft_printf("\ndata->env: %p\n", data->env);
	ft_printf("data->cmds: %p\n", data->cmds);
	ft_printf("data->status: %d\n", data->status);
	ft_printf("data->home: %p\n", data->home);
	ft_printf("data->pwd: %p\n", data->pwd);
	ft_printf("data->oldpwd: %p\n", data->oldpwd);
	ft_printf("data->stdin: %d\n", data->stdi);
	ft_printf("data->stdout: %d\n", data->stdo);
}