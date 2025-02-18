/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:40:28 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/29 11:58:07 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	check_mark(t_marks *marks, char *c, int i)
{
	if (i != 0 && c[i - 1] == '\\')
		return (0);
	if (c[i] == '\'' && marks->_1 == 0 && marks->_2 == 0)
		return (marks->_1 = 1, 1);
	else if (c[i] == '"' && marks->_1 == 0 && marks->_2 == 0)
		return (marks->_2 = 1, 1);
	else if (c[i] == '\'' && marks->_1 == 1)
		return (marks->_1 = 0, 0);	
	else if (c[i] == '"' && marks->_2 == 1)
		return (marks->_2 = 0, 0);
	return (0);
}

/* 
while str
	if str == '"'
		while str != '"' && str
			concatenate str
	else if str == '\''
		while str != '\'' && str
			concatenate str
	else
		concatenate str
*/

int	count_arg(char *line)
{
	int		count;
	int		i;
	t_marks	marks;

	i = 0;
	count = 0;
	marks._1 = 0;
	marks._2 = 0;
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ' && marks._1 == 0 && marks._2 == 0)
			i++;
		if (check_mark(&marks, line, i))
			count++;
		else if (((line[i - 1] == ' ' && line[i])
			|| (line[i - 1] != ' ' && i == 0))
			&& marks._1 == 0 && marks._2 == 0)
			count++;
		i++;
	}
	return (count);
}

char	*remove_marks(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	j = 0;
	while (str[++i])
		if (!((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\'))
			j++;
	ret = ft_calloc(i + 1, 1);
	i = -1;
	j = 0;
	while (str[++i])
		if (!((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\'))
			ret[j++] = str[i];
	return(free(str), ret);
}

char	*copy_arg(char *start, char *end)
{
	int		i;
	char	*ret;

	i = 0;
	while (&start[i] != end)
		i++;
	ret = ft_calloc(++i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (--i >= 0)
		ret[i] = start[i];
	ret = remove_marks(ret);
	return (ret);
}

char	**slice_args(char *line)
{
	int		i;
	int		y;
	t_marks	marks;
	char	**args;

	i = 0;
	y = 0;
	marks._1 = 0;
	marks._2 = 0;
	args = (char **)malloc((count_arg(line) + 1) * sizeof(char *));
	while (line[i] && line[i] != '|')
	{
		while (line[i] && line[i] == ' ')
			i++;
		args[y] = &line[i];
		while (line[i] && line[i] != ' ')
		{
			check_mark(&marks, line, i++);
			while (line[i] && (marks._1 != 0 || marks._2 != 0))
				check_mark(&marks, line, i++);
		}
		args[y] = copy_arg(args[y], (&line[i - 1]));
		y++;
	}
	return (args[y] = NULL, args);
}

t_words	*parse_words(char *line)
{
	t_words	*words;

	(void)line;
	words = (t_words *)malloc(sizeof(t_words));
	return (words);
}