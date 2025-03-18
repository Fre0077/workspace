/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:13 by fre007            #+#    #+#             */
/*   Updated: 2025/03/17 17:59:04 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printa tutta al  lista delle parole
void	print_word(t_words *words)
{
	printf("words:-----\n");
	while (words != NULL)
	{
		printf("%s\n", words->word);
		words = words->next;
	}
	printf("%p\n", words);
	printf("-----------\n");
}

//printa il file_i e il delimiter del cmds
void	print_i_delimiter(t_cmd *cmds)
{
	int	i;

	i = -1;
	printf("file_i: ");
	if (cmds->file_i != NULL)
	{
		while (cmds->file_i[++i] != NULL)
			printf("%s, ", cmds->file_i[i]);
		printf("(nil)\n");
	}
	else
		printf("(nil)\n");
	i = -1;
	printf("delimiter: ");
	if (cmds->delimiter != NULL)
	{
		while (cmds->delimiter[++i] != NULL)
			printf("%s, ", cmds->delimiter[i]);
		printf("(nil)\n");
	}
	else
		printf("(nil)\n");
}

//printa tutta la lista dei comandi
void	print_cmd(t_cmd *cmds)
{
	int	i;

	printf("cmds:-----\n");
	while (cmds != NULL)
	{
		printf("cmd: '%s'\n", cmds->cmd);
		i = -1;
		printf("arg: ");
		if (cmds->args != NULL)
		{
			while (cmds->args[++i] != NULL)
				printf("%s, ", cmds->args[i]);
			printf("%p\n", cmds->args[i]);
		}
		else
			printf("(nil)\n");
		printf("divider: %s\n", cmds->divider);
		printf("file_o: %s\n", cmds->file_o);
		printf("file_a: %s\n", cmds->file_a);
		print_i_delimiter(cmds);
		printf("next: %p\n", cmds->next);
		cmds = cmds->next;
	}
	printf("----------\n");
}

//printa tutta la struct data
void	print_data(t_data *data)
{
	printf("\ndata->env: %p\n", data->env);
	printf("data->cmds: %p\n", data->cmds);
	printf("data->status: %d\n", data->status);
	printf("data->home: %p\n", data->home);
	printf("data->pwd: %p\n", data->pwd);
	printf("data->stdin: %d\n", data->stdi);
	printf("data->stdout: %d\n", data->stdo);
}
