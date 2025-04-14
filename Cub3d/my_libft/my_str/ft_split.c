/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:42:26 by alborghi          #+#    #+#             */
/*   Updated: 2024/11/21 14:08:19 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;
	char	**split;

	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			words++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	split = (char **)malloc((words + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = NULL;
	return (split);
}

static void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	split_helper(char **split, const char *s, size_t dist, char c)
{
	size_t	j;

	j = 0;
	while (split[j] != NULL)
		j++;
	split[j] = ft_substr(s, 0, dist);
	if (!split[j])
	{
		free_split(split);
		return (-1);
	}
	j++;
	split[j] = NULL;
	while (s[dist] == c && s[dist] != '\0')
		dist++;
	return (dist);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*tmp;
	size_t	i;
	int		d;

	if (!s)
		return (NULL);
	split = ft_count_words(s, c);
	if (!split)
		return (NULL);
	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		tmp = ft_strchr(&s[i], c);
		if (tmp)
			d = split_helper(split, &s[i], tmp - &s[i], c);
		else
			d = split_helper(split, &s[i], ft_strlen(&s[i]), c);
		if (d == -1)
			return (NULL);
		i += d;
	}
	return (split);
}

/* int main()
{
	char const *s;
	s = ft_strdup("               Hello World! 42");
	char c = ' ';
	char **split = ft_split(s, c);
	size_t i = 0;
	if (!split)
		return (0);
	while (split[i] != NULL)
	{
		printf("%s\n", split[i]);
		i++;
	}
	free_split(split);
	free((char *)s);
	return (0);
} */