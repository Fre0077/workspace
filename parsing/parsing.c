/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/03/06 16:15:39 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	empty_cmd(t_cmd *cmds)
{
	cmds->cmd = NULL;
	cmds->args = NULL;
}

//se stai veramente leggendo questa descrizione ho paura il il tuo QI
int	count_args(t_words **words)
{
	t_words	*tmp;
	int		i;

	(*words) = (*words)->next;
	tmp = *words;
	i = -1;
	while ( ++i + 1 && tmp != NULL && tmp->pipe == 0)
		tmp = tmp->next;
	return (i);
}

//scrive il comando all'interno di un nodo della lista cmds
void	command_slicer(t_cmd *cmds, t_words **words, t_data *data, t_words **h)
{
	int		i;
	int		j;

	(*words) = inout_manager(*words, data, cmds);
	// print_word(*words);
	if (h != NULL)
		(*h) = (*words);
	if (data->status || (*words) == NULL)
		return (empty_cmd(cmds));
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

	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		ft_exit(data, 1);
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
	ft_exit(data, 1);
	command_slicer(cmds, &words, data, &head);
	first = cmds;
	while (words != NULL)
	{
		if (words->pipe == 1)
			words = words->next;
		else
			cmds = new_command(cmds, &words, data);
	}
	cmds->next = NULL;
	// print_cmd(first);
	return (free_words_only_pointers(head), first);
}
