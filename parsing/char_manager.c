/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:11:55 by fre007            #+#    #+#             */
/*   Updated: 2025/03/05 10:51:12 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//controlla la posizione rispetto alle quote
int	quote_checker(char *line, int i)
{
	static int	mark;

	if (!line[i])
		return (mark = 0, 0);
	if (line[i] == '\'')
	{
		if ((i == 0 && mark == 0) || (mark == 0 && line[i - 1] != '\\'))
			mark = 1;
		else if (i > 0 && line[i - 1] != '\\' && mark == 1)
			mark = 0;
	}
	if (line[i] == '\"')
	{
		if ((i == 0 && mark == 0) || (mark == 0 && line[i - 1] != '\\'))
			mark = 2;
		else if (i > 0 && line[i - 1] != '\\' && mark == 2)
			mark = 0;
	}
	if (mark == 2)
		return (2);
	if (mark == 1)
		return (1);
	return (0);
}

//duplica per n cartterei (funzionante)
char	*dup_till_n(char *start, int n, t_data *data)
{
	char	*str;

	str = (char *)ft_calloc(1, n + 1);
	if (!str)
		ft_exit(data, 1);
	while (--n >= 0)
		str[n] = start[n];
	return (str);
}

//data la stringa rimuove il carattere ocrrispondente al numero dato (funzia)
char	*remove_char(char *word, int i, t_data *data)
{
	char	*new_word;
	int		j;
	int		l;

	new_word = ft_calloc(1, ft_strlen(word));
	if (!new_word)
		ft_exit(data, 1);
	j = -1;
	l = -1;
	while (i != ++j)
		new_word[++l] = word[j];
	while (word[++j])
		new_word[++l] = word[j];
	return (free(word), new_word);
}
