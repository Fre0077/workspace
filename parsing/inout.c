/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:21:59 by fre007            #+#    #+#             */
/*   Updated: 2025/03/07 09:55:12 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//prende quello subito dopo alla stringa find
char	*find_after_word(char *find, t_words **tmp, t_data *data)
{
	t_words	*first;
	char	*finded;
	char	*ret;

	first = (*tmp);
	while ((*tmp) != NULL && (*tmp)->pipe == 0)
	{
		finded = ft_strstr((*tmp)->word, find);
		if (finded != NULL)
			break ;
		(*tmp) = (*tmp)->next;
	}
	if (finded == NULL || (!finded[ft_strlen(find)] && (*tmp)->next == NULL))
		return ((*tmp) = first, NULL);
	if (check_sintax_error(*tmp, finded, find, data))
		return (NULL);
	ret = NULL;
	if (ft_strlen(find) == ft_strlen((*tmp)->word))
		ret = clear_2_node(tmp, &first, data);
	else if (ft_strlen(find) == ft_strlen(finded))
		ret = clear_next_node(tmp, finded, &first, data);
	else if (ft_strlen((*tmp)->word) == ft_strlen(finded))
		ret = clear_this_node(tmp, &finded[ft_strlen(find)], &first, data);
	else if (finded[ft_strlen(find)])
		ret = remove_last_part(tmp, finded, find, data);
	return ((*tmp) = first, ret);
}

char	*findable_file(t_words *words)
{
	t_words	*tmp;
	int		i;

	tmp = words;
	while (tmp != NULL && tmp->pipe == 0)
	{
		i = 0;
		while (tmp->word != NULL && tmp->word[i]
			&& ((quote_checker(tmp->word, i)
					&& ft_strchr("<>", tmp->word[i]))
				|| !ft_strchr("<>", tmp->word[i])))
			i++;
		if (tmp->word == NULL || !tmp->word[i])
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->word[i] != tmp->word[i + 1])
			return (ft_strndup(&(tmp->word[i]), 1));
		else
			return (ft_strndup(&(tmp->word[i]), 2));
		tmp = tmp->next;
	}
	quote_checker("1", 1);
	return (NULL);
}

// apre e chiude un file che non viene utilizzato
void	open_useless_file(t_cmd *cmds, int witch)
{
	int	fd;

	if (witch == 1)
		cmds->file_a = NULL;
	else if (witch == 2)
		cmds->file_i = NULL;
	if (cmds->file_o != NULL)
	{
		fd = open(cmds->file_o, O_CREAT, 0644);
		if (fd == -1)
			return ;
		free (cmds->file_o);
		cmds->file_o = NULL;
		close(fd);
	}
	else if (cmds->file_a != NULL)
	{
		fd = open(cmds->file_a, O_CREAT, 0644);
		if (fd == -1)
			return ;
		free (cmds->file_a);
		cmds->file_a = NULL;
		close(fd);
	}
}

//gestisce la sovrascittura di nuovi nomi file
void	check_file(char *find, t_words **words, t_cmd *cmds, t_data *data)
{
	char	*finded;

	finded = find_after_word(find, words, data);
	if (finded == NULL)
		return ;
	if (ft_strncmp(find, ">>", 3) == 0)
	{
		open_useless_file(cmds, 2);
		cmds->file_a = finded;
	}
	else if (ft_strncmp(find, ">", 2) == 0)
	{
		open_useless_file(cmds, 1);
		cmds->file_o = finded;
	}
	if (ft_strncmp(find, "<<", 3) == 0)
	{
		cmds->doi = 2;
		cmds->delimiter = ft_append_line(cmds->delimiter, finded);
	}
	else if (ft_strncmp(find, "<", 2) == 0)
	{
		cmds->doi = 1;
		cmds->file_i = ft_append_line(cmds->file_i, finded);
	}
}

//verifica tutte le informazioni per i simboli: <, <<, >>, >
t_words	*inout_manager(t_words *words, t_data *data, t_cmd *cmds, int end)
{
	char	*find;
	t_words	*tmp;

	cmds->file_o = NULL;
	cmds->file_a = NULL;
	cmds->file_i = NULL;
	cmds->delimiter = NULL;
	cmds->doi = 0;
	find = findable_file(words);
	while (find != NULL)
	{
		data->find = find;
		check_file(find, &words, cmds, data);
		free (find);
		if (data->status)
			break ;
		find = findable_file(words);
	}
	tmp = words;
	while (end && tmp != NULL)
		tmp = dollar_manager(data, tmp);
	return (words);
}
