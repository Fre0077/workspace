/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:12:38 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/23 17:13:01 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_readline(char *s1, char *s2)
{
	char	*join;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (join);
}

char	*ft_readline(char *prompt)
{
	char	*line;

	//signal(SIGC, free_line());
	ft_printf("%s", prompt);
	line = get_next_line(0);
	while (line != NULL && ft_strchr(line, '\n') == NULL && g_signal == 0)
	{
		line = ft_strjoin_readline(line, get_next_line(0));
		// ft_printf("%s\n", line);
	}
	return (line);
}
