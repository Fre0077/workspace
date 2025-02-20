/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:02:13 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/21 09:45:47 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*search;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	dest = (unsigned char *) dst;
	search = (unsigned char *) src;
	i = -1;
	while (++i < n)
		dest[i] = search[i];
	return (dst);
}

/* int main()
{
	char *cane[12];
	char *gatto = "ciao min va!";
	printf("%s", (char *)ft_memcpy(cane, gatto, 12));
} */