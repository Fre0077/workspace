/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 20:20:42 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/23 20:51:21 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(*s1) * len_s1 + len_s2 + 1);
	if (!str)
		return (NULL);
	str[len_s1 + len_s2] = '\0';
	while (--len_s2 >= 0)
		str[len_s1 + len_s2] = s2[len_s2];
	while (--len_s1 >= 0)
		str[len_s1] = s1[len_s1];
	return (str);
}

/* int main()
{
	printf("%s", ft_strjoin("NULL", "NULL"));
} */