/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:01:48 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/23 21:00:41 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*copy;
	int		i;

	len = ft_strlen(s1);
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}
