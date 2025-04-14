/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:58:34 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/07 10:50:24 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = (char *)ft_calloc(len, sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len);
	return (dup);
}

char	*ft_strndup(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*str_dup_till_charset(const char *str, const char *charset)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && !ft_strchr(charset, str[i]))
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, i + 1);
	return (ret);
}

char	**ft_char_mat_dup(char **mat)
{
	int		i;
	char	**new;

	i = 0;
	while (mat[i])
		i++;
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new)
		return (0);
	i = 0;
	while (mat[i])
	{
		new[i] = ft_strdup(mat[i]);
		if (!new[i])
		{
			ft_free_mat_char(new);
			return (0);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}
