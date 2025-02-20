/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:43:07 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/21 09:45:34 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	i = len;
	if (dst > src)
		while (--i >= 0)
			((char *)dst)[i] = ((char *)src)[i];
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

/* int main()
{
	char wer[6] = "gatto";
	char ter[6] = "catto";

	printf("%s", (char *)ft_memmove(wer, ter, 5));
} */