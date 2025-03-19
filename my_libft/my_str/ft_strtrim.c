/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:31:04 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/19 11:03:50 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	len;
	int	trim;

	len = ft_strlen(s1);
	trim = 0;
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	while (len > trim && ft_strchr(set, s1[trim]))
		trim++;
	return (ft_substr(s1, trim, len - trim));
}

char	*ft_strtrim_free(char const *s1, char const *set)
{
	int		len;
	int		trim;
	char	*tmp;

	len = ft_strlen(s1);
	trim = 0;
	while (len > 0 && ft_strchr(set, s1[len - 1]))
		len--;
	while (len > trim && ft_strchr(set, s1[trim]))
		trim++;
	tmp = ft_substr(s1, trim, len - trim);
	free((char *)s1);
	return (tmp);
}
