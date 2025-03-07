/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:13 by fre007            #+#    #+#             */
/*   Updated: 2025/03/07 14:24:48 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printa tutta al  lista delle parole
void	print_word(t_words *words)
{
	ft_printf("words:-----\n");
	while (words != NULL)
	{
		ft_printf("%s\n", words->word);
		words = words->next;
	}
	ft_printf("%p\n", words);
	ft_printf("-----------\n");
}

//printa il file_i e il delimiter del cmds
void	print_i_delimiter(t_cmd *cmds)
{
	int	i;

	i = -1;
	ft_printf("file_i: ");
	if (cmds->file_i != NULL)
	{
		while (cmds->file_i[++i] != NULL)
			ft_printf("%s, ", cmds->file_i[i]);
		ft_printf("%s\n", cmds->file_i[i]);
	}
	else
		ft_printf("(nil)\n");
	i = -1;
	ft_printf("delimiter: ");
	if (cmds->delimiter != NULL)
	{
		while (cmds->delimiter[++i] != NULL)
			ft_printf("%s, ", cmds->delimiter[i]);
		ft_printf("%s\n", cmds->delimiter[i]);
	}
	else
		ft_printf("(nil)\n");
}

//printa tutta la lista dei comandi
void	print_cmd(t_cmd *cmds)
{
	int	i;

	ft_printf("cmds:-----\n");
	while (cmds != NULL)
	{
		ft_printf("cmd: %s\n", cmds->cmd);
		i = -1;
		ft_printf("arg: ");
		if (cmds->args != NULL)
		{
			while (cmds->args[++i] != NULL)
				ft_printf("%s, ", cmds->args[i]);
			ft_printf("%s\n", cmds->args[i]);
		}
		else
			ft_printf("(nil)\n");
		ft_printf("divider: %s\n", cmds->divider);
		ft_printf("file_o: %s\n", cmds->file_o);
		ft_printf("file_a: %s\n", cmds->file_a);
		print_i_delimiter(cmds);
		ft_printf("next: %p\n", cmds->next);
		cmds = cmds->next;
	}
	ft_printf("----------\n");
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
