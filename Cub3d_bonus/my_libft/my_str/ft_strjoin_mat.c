/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_mat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:35:21 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/18 17:43:46 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_1(char *s1, char *s2)
{
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, ft_strlen(s1) + 1);
	ft_strlcat(join, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	return (join);
}

// char	*ft_strjoin_mat(char **mat, char *sep)
// {
// 	char	*str;
// 	int		i;

// 	if (!mat || !*mat)
// 		return (NULL);
// 	i = 0;
// 	str = ft_strdup("");
// 	{
// 		str = ft_strjoin_free_1(str, mat[i]);
// 		if (mat[i + 1] && sep)
// 			str = ft_strjoin_free_1(str, sep);
// 		i++;
// 	}

// 	return (str);
// }
