/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:21:59 by fre007            #+#    #+#             */
/*   Updated: 2025/02/24 18:15:51 by alborghi         ###   ########.fr       */
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
	t_words *tmp_first;

	tmp_first = first;
	while (tmp_first->next != words)
		tmp_first = tmp_first->next;
	tmp = words;
	tmp_first->next = words->next;
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

	if ((*tmp) == (*first))
		(*first) = (*tmp)->next;
	(*tmp) = remove_node_words(*tmp, *first);
	ret = ft_strdup((*tmp)->word);
	if (ret == NULL)
		ft_exit(data);
	if ((*tmp) == (*first))
		(*first) = (*tmp)->next;
	(*tmp) = remove_node_words(*tmp, *first);
	return (dollar_manager(ret, data));
}

char	*clear_next_node(t_words **tmp, char *finded, t_words **first, t_data *data)
{
	char	*ret;

	ret = ft_strdup((*tmp)->next->word);
	if (ret == NULL)
		ft_exit(data);
	remove_node_words((*tmp)->next, *first);
	(*tmp)->word = remove_finded((*tmp)->word, finded, data);
	return (dollar_manager(ret, data));
}

char	*clear_this_node(t_words **tmp, char *finded, t_words **first, t_data *data)
{
	char	*ret;

	ret = ft_strdup(finded);
	if (ret == NULL)
		ft_exit(data);
	if ((*tmp) == (*first))
		(*first) = (*tmp)->next;
	(*tmp) = remove_node_words(*tmp, *first);
	return (dollar_manager(ret, data));
}

char	*remove_last_part(t_words **tmp, char *finded, char *find, t_data *data)
{
	char	*ret;

	ret = ft_strdup(&finded[ft_strlen(find)]);
	if (ret == NULL)
		ft_exit(data);
	(*tmp)->word = remove_finded((*tmp)->word, finded, data);
	return (dollar_manager(ret, data));
}

//prende quello subito dopo alla stringa find
char	*find_after_word(char *find, t_words **tmp, t_data *data)
{
	t_words	*first;
	char	*finded;
	char	*ret;

	first = (*tmp);
	ret = NULL;
	while ((*tmp) != NULL)
	{
		finded = ft_strstr((*tmp)->word, find);
		if (finded != NULL)
			break ;
		(*tmp) = (*tmp)->next;
	}
	if (finded == NULL || (!finded[ft_strlen(find)] && (*tmp)->next == NULL))
		return ((*tmp) = first, NULL);
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

int	findable_file(t_words *words)
{
	t_words	*tmp;

	tmp = words;
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->word, "<") != NULL)
			return (1);
		tmp = tmp->next;
	}
	tmp = words;
	while (tmp != NULL)
	{
		if (ft_strstr(tmp->word, ">") != NULL)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

//verifica tutte le informazioni per i simboli: <, <<, >>, >
t_words	*inout_manager(t_words *words, t_data *data)
{
	(void)data;
	t_words	*tmp;

	data->file_i = NULL;
	data->file_o = NULL;
	data->file_a = NULL;
	data->delimiter = NULL;
	while (findable_file(words))
	{
		data->delimiter = find_after_word("<<", &words, data);
		if (data->delimiter == NULL)
			data->file_i = find_after_word("<", &words, data);
		data->file_a = find_after_word(">>", &words, data);
		if (data->file_a == NULL)
			data->file_o = find_after_word(">", &words, data);
	}
	tmp = words;
	while (tmp != NULL)
	{
		tmp->word = dollar_manager(tmp->word, data);
		tmp = tmp->next;
	}
	return (words);
}
