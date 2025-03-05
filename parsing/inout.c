/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:21:59 by fre007            #+#    #+#             */
/*   Updated: 2025/03/05 17:40:40 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

//trova un stringa in un'altra stringa
char	*ft_strstr(char *big, char *little)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (little != NULL && big[i])
	{
		check = quote_checker(big, i);
		j = 0;
		while (big[i + j] == little[j] && little[j] && !check)
			j++;
		if (!little[j])
		{
			quote_checker("1", 1);
			return (&big[i]);
		}
		i++;
	}
	quote_checker("1", 1);
	return (NULL);
}

//rimuove un nodo della lista ricollegandola
t_words	*remove_node_words(t_words *words, t_words *first)
{
	t_words *tmp;

	if (first == words)
	{
		tmp = words->next;
		free (words->word);
		free (words);
		return (tmp);
	}
	while (first && first->next != words)
		first = first->next;
	if (first == NULL)
		return (first);
	tmp = words;
	first->next = words->next;
	free (words->word);
	words = words->next;
	free (tmp);
	return (words);
}

//rimuove il pezzo di stringa contenente il finded
char	*remove_finded(char *word, char *finded, t_data *data)
{
	int		i;
	char	*new_word;

	i = -1;
	new_word = ft_calloc(1, ft_strlen(word) - ft_strlen(finded) + 1);
	if (!new_word)
		ft_exit(data);
	while (word[++i])
	{
		if (ft_strlen(&word[i]) == ft_strlen(finded))
			break ;
		new_word[i] = word[i];
	}
	return (free (word), new_word);
}

char	*clear_2_node(t_words **tmp, t_words **first, t_data *data)
{
	char	*ret;
	t_words	*tmp_first;

	tmp_first = *first;
	if ((*tmp) == (*first))
		(*first) = (*first)->next;
	(*tmp) = remove_node_words(*tmp, tmp_first);
	ret = ft_strdup((*tmp)->word);
	if (ret == NULL)
		ft_exit(data);
	tmp_first = *first;
	if ((*tmp) == (*first))
		(*first) = (*first)->next;
	(*tmp) = remove_node_words(*tmp, tmp_first);
	return (dollar_manager_stupid(ret, data));
}

char	*clear_next_node(t_words **tmp, char *finded, t_words **first, t_data *data)
{
	char	*ret;
	t_words	*tmp_first;

	tmp_first = *first;
	ret = ft_strdup((*tmp)->next->word);
	if (ret == NULL)
		ft_exit(data);
	remove_node_words((*tmp)->next, tmp_first);
	(*tmp)->word = remove_finded((*tmp)->word, finded, data);
	return (dollar_manager_stupid(ret, data));
}

char	*clear_this_node(t_words **tmp, char *finded, t_words **first, t_data *data)
{
	char	*ret;
	t_words	*tmp_first;

	tmp_first = *first;
	ret = ft_strdup(finded);
	if (ret == NULL)
		ft_exit(data);
	if ((*tmp) == (*first))
		(*first) = (*tmp)->next;
	(*tmp) = remove_node_words(*tmp, tmp_first);
	return (dollar_manager_stupid(ret, data));
}

char	*remove_last_part(t_words **tmp, char *finded, char *find, t_data *data)
{
	char	*ret;

	ret = ft_strdup(&finded[ft_strlen(find)]);
	if (ret == NULL)
		ft_exit(data);
	(*tmp)->word = remove_finded((*tmp)->word, finded, data);
	return (dollar_manager_stupid(ret, data));
}

//controlla che non ci sia un errore di sintassi. < seguito da un altro <
int	check_sintax_error(t_words *tmp, char *finded, char *find, t_data *data)
{
	if (finded[ft_strlen(find)] == '<' || finded[ft_strlen(find)] == '>')
		data->status = 1;
	if (!finded[ft_strlen(find)] &&
		(tmp->next->word[0] == '<' || tmp->next->word[0] == '>'))
		data->status = 1;
	return (data->status);
}

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
		while (tmp->word[i] && tmp->word[i] != '<' && tmp->word[i] != '>')
			i++;
		if (!tmp->word[i])
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
	return (NULL);
}

void	dollar_cicle(t_words *words, t_data	*data)
{
	t_words	*tmp;

	tmp = words;
	while (tmp != NULL)
	{
		tmp->word = dollar_manager(tmp->word, data);
		tmp = tmp->next;
	}
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
t_words	*inout_manager(t_words *words, t_data *data, t_cmd *cmds)
{
	char	*find;

	cmds->file_i = NULL;
	cmds->file_o = NULL;
	cmds->file_a = NULL;
	cmds->delimiter = NULL;
	cmds->doi = 0;
	find = findable_file(words);
	while (find != NULL)
	{
		check_file(find, &words, cmds, data);
		free (find);
		if (data->status)
			break ;
		find = findable_file(words);
	}
	dollar_cicle(words, data);
	return (words);
}
