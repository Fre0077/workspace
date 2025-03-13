/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 21:34:49 by fre007            #+#    #+#             */
/*   Updated: 2025/03/13 22:33:44 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_next_heredoc(char *line, t_data *data)
{
	int		i;
	int 	j;
	char	*str;

	i = 0;
	while (line[i] == ' ' && !quote_checker(line, i))
		i++;
	if (ft_strchr("<>", line[i]) || !line[i])
		return (NULL);
	j = i;
	while (ft_strchr("<> ", line[i]) == NULL || quote_checker(line, i))
		i++;
	str = dup_till_n(&line[j], i - j, data);
	return(str);
}

void	find_heredoc_only(char *line, t_data * data)
{
	char	**arr;
	char	*str;
	int		i;

	i = -1;
	arr = NULL;
	str = NULL;
	while (line[++i])
	{
		if (i != 0 && line[i - 1] == '<' && line[i] == '<'
			&& line[i + 1] != '<'&& line[i + 1] != '>')
		{
			str = find_next_heredoc(&line[i + 1], data);
			arr = ft_append_line(arr, str);
		}
	}
	handle_delimiter(arr, 2, data);
	ft_free_mat_char(arr);
}