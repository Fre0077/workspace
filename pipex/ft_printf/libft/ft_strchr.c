/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:27:11 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 13:58:19 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == (char)c)
			return ((char *)str + i);
	if (str[i] == (char)c)
		return ((char *)str + i);
	return (NULL);
}

/* int main()
{
	printf("%s", strchr("gatto", 98));
} */