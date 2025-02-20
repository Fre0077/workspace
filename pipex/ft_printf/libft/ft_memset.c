/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:25:08 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/23 20:28:04 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *buffer, int c, size_t count)
{
	char	*str;
	size_t	i;

	str = (char *)buffer;
	if (!str)
		return (NULL);
	i = 0;
	while (i < count)
		str[i++] = (unsigned char)c;
	return (buffer);
}
