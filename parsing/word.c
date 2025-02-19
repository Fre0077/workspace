/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:12:42 by fre007            #+#    #+#             */
/*   Updated: 2025/02/18 18:59:53 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//crea uan stringa allocata contenente | (funzia)
char	*pipe_manager(int *i)
{
	char	*str;

	str = ft_calloc(1, 2);
	str[0] = '|';
	*i += 1;
	return (str);
}

//restittuisce la porssima parola all'interno della stringa (funzia)
char	*next_word(char *line, int *i, t_data *data)
{
	int		start;
	char	*word;

	if (line == NULL)
		return (NULL);
	start = *i;
	while ((quote_checker(line, *i) || (line[*i] != ' ' && line[*i] != '|')) && line[*i])
		*i += 1;
	word = dup_till_n(&line[start], *i - start);
	word = dollar_manager(word, data);
	return (word);
}

//alloca il prossimo elemento della lista e lo collega mettendo dentro il valore (funzia)
t_words	*new_word(t_words *words, char *str)
{
	words->next = malloc(sizeof(t_words));
	words = words->next;
	words->word = str;
	return (words);
}

//divide la linea in parti considerando le quote (funzionante)
//non piglia le virgolette se sono all'inizio (risolto)
//l'ultimo elemento non è nul ma un nodo vuoto, sarebbe meglio fixare questa cosa(risolto)
t_words	*word_slicer(char *line, t_data *data)
{
	int		i;
	t_words	*first;
	t_words	*words;

	i = 0;
	while (line[i] == ' ')
		i++;
	words = malloc(sizeof(t_words));
	words->word = next_word(line, &i, data);
	first = words;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '|')
			words = new_word(words, next_word(line, &i, data));
		else if (line[i] == '|')
			words = new_word(words, pipe_manager(&i));
		else
			i++;
	}
	return (words->next = NULL, first);
}
