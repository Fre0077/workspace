/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/02/27 17:15:57 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//scrive il comando all'interno di un nodo della lista cmds
void	command_slicer(t_cmd *cmds, t_words **words, t_data *data, t_words **h)
{
	t_words	*arg;
	int		i;
	int		j;

	(*words) = inout_manager(*words, data, cmds);
	if (h != NULL)
		(*h) = (*words);
	cmds->cmd = (*words)->word;
	arg = (*words)->next;
	(*words) = (*words)->next;
	i = 0;
	while ((*words) != NULL && (*words)->word[0] != '|')
	{
		(*words) = (*words)->next;
		i++;
	}
	cmds->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(cmds->args))
		ft_exit(data);
	cmds->args[i] = NULL;
	j = -1;
	while (--i >= 0)
	{
		cmds->args[++j] = arg->word;
		arg = arg->next;
	}
}

//crea un nuovo nodo per la lista cmds
t_cmd	*new_command(t_cmd *cmds, t_words **words, t_data *data)
{
	t_cmd	*new_cmd;

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		ft_exit(data);
	cmds->next = new_cmd;
	command_slicer(new_cmd, words, data, NULL);
	return (new_cmd);
}

void	free_words_only_pointers(t_words *words)
{
	t_words	*tmp;

	while (words != NULL)
	{
		tmp = words;
		words = words->next;
		if (ft_strncmp(tmp->word, "|", 2) == 0)
			free(tmp->word);
		free(tmp);
	}
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
	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		ft_exit(data);
	command_slicer(cmds, &words, data, &head);
	first = cmds;
	while (words != NULL)
	{
		if (words->word[0] == '|')
			words = words->next;
		else
			cmds = new_command(cmds, &words, data);
	}
	cmds->next = NULL;
	return (free_words_only_pointers(head), first);
}
