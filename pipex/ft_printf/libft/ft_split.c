/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:03:36 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/26 16:05:30 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean_array(char **array, int count)
{
	while (count > 0)
		free(array[count--]);
}

static int	word_len(char const *s, char c, char **array)
{
	int	i;
	int	len;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		len = 0;
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c && s[i]))
			while ((s[i] != c && s[i]) || len++)
				i++;
		if (len != 0)
		{
			array[count] = malloc(sizeof(char) * (len + 1));
			if (!array[count])
				return (clean_array(array, count), 1);
			array[count++][len] = '\0';
		}
	}
	return (0);
}

static int	count_word(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;
	int		pos;
	int		i;

	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!array || word_len(s, c, array) == 1)
		return (NULL);
	count = 0;
	i = -1;
	while (s[++i])
	{
		pos = 0;
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c && s[i]))
		{
			while (s[i] != c && s[i])
				array[count][pos++] = s[i++];
			count++;
		}
	}
	array[count] = NULL;
	return (array);
}

/* int main()
{
	char	**array;
	int		i;

	i = -1;
	array = ft_split("87876  ttret et tes", ' ');
	while (array[++i] != NULL)
		printf("%s\n", array[i]);
	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
} */