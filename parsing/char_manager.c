/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:11:55 by fre007            #+#    #+#             */
/*   Updated: 2025/02/19 15:04:48 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//duplica per n cartterei (funzionante)
char	*dup_till_n(char *start, int n)
{
	char	*str;

	str = ft_calloc(1, n + 1);
	while (--n >= 0)
		str[n] = start[n];
	return (str);
}

//data la stringa rimuove il carattere ocrrispondente al numero dato (funzia)
char	*remove_char(char *word, int *i)
{
	char	*new_word;
	int		j;
	int		l;

	new_word = ft_calloc(1, ft_strlen(word));
	j = -1;
	l = -1;
	while (word[++j])
	{
		if (*i == j)
			j++;
		new_word[++l] = word[j];
	}
	return (free(word), new_word);
}

