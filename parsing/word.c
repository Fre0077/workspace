/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:12:42 by fre007            #+#    #+#             */
/*   Updated: 2025/03/12 18:54:25 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//crea una stringa allocata contenente |
t_words	*pipe_manager(int *i, t_data *data, t_words *words)
{
	char	*str;

	words->next = malloc(sizeof(t_words));
	if (!words->next)
		ft_exit(data, 1);
	str = (char *)ft_calloc(1, 2);
	if (!str)
		ft_exit(data, 1);
	str[0] = '|';
	words = words->next;
	words->word = str;
	words->pipe = 1;
	*i += 1;
	return (words);
}

//restittuisce la porssima parola all'interno della stringa
char	*next_word(char *line, int *i, t_data *data)
{
	int		start;
	char	*word;

	if (line == NULL)
		return (NULL);
	start = *i;
	while ((quote_checker(line, *i) || (line[*i] != ' ' && line[*i] != '|'))
		&& line[*i])
		*i += 1;
	word = dup_till_n(&line[start], *i - start, data);
	return (word);
}

//crea il prossimo nodo della lista words e imposta il valore passatogli
t_words	*new_word(t_words *words, char *str, t_data *data)
{
	words->next = malloc(sizeof(t_words));
	if (!words->next)
		ft_exit(data, 1);
	words = words->next;
	words->word = str;
	words->pipe = 0;
	return (words);
}

//divide l'imput in parti con le regole di parsing del bash
t_words	*word_slicer(char *line, t_data *data)
{
	int		i;
	t_words	*first;
	t_words	*words;

	i = 0;
	while (line[i] == ' ')
		i++;
	// if (line[i] == '\0')
	// 	return (NULL);
	words = (t_words *)malloc(sizeof(t_words));
	if (!words)
		ft_exit(data, 1);
	words->word = next_word(line, &i, data);
	words->pipe = 0;
	first = words;
	while (line[i])
	{
		if ((line[i] != ' ' && line[i] != '|') || quote_checker(line, i))
			words = new_word(words, next_word(line, &i, data), data);
		else if (line[i] == '|' && !quote_checker(line, i))
			words = pipe_manager(&i, data, words);
		else
			i++;
	}
	return (words->next = NULL, first);
}
