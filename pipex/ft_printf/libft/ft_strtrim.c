/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:13:48 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/25 14:55:22 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	k = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[k]))
		k--;
	str = ft_substr(s1, i, (k - i) + 1);
	return (str);
}

/* int main()
{
	printf("%s", ft_strtrim("d	gg", NULL));
} */
