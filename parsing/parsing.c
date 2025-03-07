/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/03/07 12:07:21 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*calloc_cmds(t_data *data)
{
	t_cmd	*cmds;

	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmds)
		ft_exit(data, 1);
	cmds->file_o = NULL;
	cmds->file_a = NULL;
	cmds->file_i = NULL;
	cmds->delimiter = NULL;
	cmds->divider = NULL;
	cmds->args = NULL;
	cmds->cmd = NULL;
	cmds->next = NULL;
	return (cmds);
}

//scrive il comando all'interno di un nodo della lista cmds
void	command_slicer(t_cmd *cmds, t_words **words, t_data *data, t_words **h)
{
	int		i;
	int		j;

	(*words) = inout_manager(*words, data, cmds);
	if (h != NULL)
		(*h) = (*words);
	if (data->status || (*words) == NULL)
		return ;
	cmds->cmd = (*words)->word;
	i = count_args(words);
	cmds->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(cmds->args))
		ft_exit(data, 1);
	cmds->args[i] = NULL;
	j = -1;
	while (--i >= 0)
	{
		cmds->args[++j] = (*words)->word;
		(*words) = (*words)->next;
	}
	cmds->divider = NULL;
	if ((*words) != NULL)
		cmds->divider = (*words)->word;
}

//crea un nuovo nodo per la lista cmds
t_cmd	*new_command(t_cmd *cmds, t_words **words, t_data *data)
{
	t_cmd	*new_cmd;

	new_cmd = calloc_cmds(data);
	cmds->next = new_cmd;
	command_slicer(new_cmd, words, data, NULL);
	return (new_cmd);
}

//crea la lista contenente la lista cmds facendo il parsing necessario
t_cmd	*parsing(char *line, t_data *data)
{
	t_words	*words;
	t_words	*head;
	t_cmd	*cmds;
	t_cmd	*first;

	if (line[0] == '\0' || line == NULL || line[0] == '\n')
		return (NULL);
	words = word_slicer(line, data);
	head = words;
	cmds = calloc_cmds(data);
	command_slicer(cmds, &words, data, &head);
	print_word(head);
	first = cmds;
	while (!data->status && words != NULL)
	{
		if (words->pipe == 1)
			words = words->next;
		else
			cmds = new_command(cmds, &words, data);
	}
	//cmds->next = NULL;
	return (free_words_only_pointers(head), first);
}
