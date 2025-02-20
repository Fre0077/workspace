/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:24:51 by fde-sant          #+#    #+#             */
/*   Updated: 2025/01/20 10:36:08 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count(char *str, int which, int where, char c)
{
	int	i;
	int	line;

	if (which == 0)
	{
		i = -1;
		line = 1;
		while (str[++i])
			if (i != 0 && str[i] == c && str[i - 1] != c)
				line++;
		return (line);
	}
	i = 0;
	while (str[i + where] || str[i + where] == '\n')
		i++;
	return (i);
}

void	copy(char *str, char **arr, char c)
{
	int	i;
	int	j;
	int	y;

	i = -1;
	j = -1;
	y = 0;
	arr[y] = malloc(count(str, 1, 0, c) + 1);
	while (str[++i])
	{
		if (str[i] != c)
			arr[y][++j] = str[i];
		else if (i != 0 && str[i] == c && str[i - 1] != c)
		{
			arr[y][++j] = '\0';
			arr[++y] = malloc(count(str, 1, i + 1, c) + 1);
			j = -1;
		}
	}
	arr[y][++j] = '\0';
	arr[++y] = NULL;
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = count(s1, 1, 0, ' ');
	len_s2 = count(s2, 1, 0, ' ');
	str = malloc(len_s1 + len_s2 + 2);
	if (!str)
		return (NULL);
	str[len_s1 + len_s2 + 1] = '\0';
	str[len_s1] = '/';
	while (--len_s2 >= 0)
		str[len_s1 + len_s2 + 1] = s2[len_s2];
	while (--len_s1 >= 0)
		str[len_s1] = s1[len_s1];
	return (str);
}

char	**ft_split_add(char *str, char *add, char c)
{
	char	**arr;
	char	*temp;
	int		i;

	if (str == NULL)
		return (NULL);
	if (c == '\0')
		return (NULL);
	i = count(str, 0, 0, c);
	arr = malloc((i + 1) * sizeof(char *));
	copy(str, arr, c);
	while (--i >= 0 && add != NULL)
	{
		temp = ft_strjoin(arr[i], add);
		free(arr[i]);
		arr[i] = temp;
	}
	return (arr);
}
