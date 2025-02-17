/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:10 by fre007            #+#    #+#             */
/*   Updated: 2025/02/17 15:10:32 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//funzione che tiene controllato se si è all'interno di virgolette tramite statica(funzionante)
int	quote_checker(char *line, int i)
{
	static int	mark;

	if (!line[i])
		return (mark = 0, 0);
	if (line[i] == '\'')
	{
		if (i == 0 || (line[i - 1] != '\\' && mark == 0))
			mark = 1;
		else if (line[i - 1] != '\\' && mark == 1)
			mark = 0;
	}
	if (line[i] == '\"')
	{
		if (i == 0 || (line[i - 1] != '\\' && mark == 0))
			mark = 2;
		else if (line[i - 1] != '\\' && mark == 2)
			mark = 0;
	}
	if (mark == 2)
		return (2);
	if (mark == 1)
		return (1);
	return (0);
}

//elimina le quote identificate da quote_checker eccetto quando c'è $(funziona)
char	*quote_remover(char *word)
{
	int	i;
	int	check;
	int	pre;

	i = -1;
	while (word[++i])
		if (word[i] == '$')
			return (word);
	i = -1;
	check = 0;
	while (word[++i])
	{
		pre = check;
		check = quote_checker(word, i);
		if (pre != check)
		{
			word = remove_char(word, i);
			i--;
		}
	}
	return (word);
}
