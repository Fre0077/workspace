/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/02/19 19:57:59 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_words(t_words *words)
{
	while (words != NULL)
	{
		free (words->word);
		words = words->next;
	}
	free (words);
}

//funzione per la scrittura dei comandi nella lista e per la creazione dei nuovi nodi
void	command_slicer(t_cmd *cmds, t_words **words)
{
	t_words	*arg;
	int		i;
	int		j;

	cmds->cmd = (*words)->word;
	arg = (*words)->next;
	(*words) = (*words)->next;
	i = 0;
	while ((*words) != NULL && (*words)->word[0] != '|') //possibile aggiunta dell '&&'
	{
		(*words) = (*words)->next;
		i++;
	}
	cmds->args = malloc(sizeof(char *) * (i + 1));
	cmds->args[i] = NULL;
	j = -1;
	while (--i >= 0)
	{
		cmds->args[++j] = arg->word;
		arg = arg->next;
	}
}

//funzione lanciata per creare un nodo della lista cmds, setta anche gli argomenti 
t_cmd	*new_command(t_cmd *cmds, t_words **words)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd));
	cmds->next = new_cmd;
	command_slicer(new_cmd, words);
	return (new_cmd);
}

//funzione principale per la gestione di tutto il parsing 
t_cmd	*parsing(char *line, t_data *data)
{
	t_words	*words;
	t_cmd	*cmds;
	t_cmd	*first;

	if (line[0] == '\0' || line == NULL || line[0] == '\n')
		return (NULL);
	words = word_slicer(line, data);
	ft_printf("--------\n");
	print_word(words);
	ft_printf("--------\n");
	cmds = malloc(sizeof(t_cmd));
	command_slicer(cmds, &words);
	first = cmds;
	while (words != NULL)
	{
		if (words->word[0] == '|')
			words = words->next;
		else
			cmds = new_command(cmds, &words);
	}
	cmds->next = NULL;
	print_cmd(first);
	ft_printf("--------\n");
	return (first);
}
