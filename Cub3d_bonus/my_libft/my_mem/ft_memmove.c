/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:50:12 by alborghi          #+#    #+#             */
/*   Updated: 2024/11/19 18:01:01 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest && !src)
		return (NULL);
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
	}
	else
	{
		while (n > 0)
		{
			((unsigned char *)dest)[n - 1] = ((unsigned char *)src)[n - 1];
			n--;
		}
	}
	return (dest);
}

/* int main()
{
	char src[] = "Ciao sono io";
	//char dest[8];
	char src1[] = "123 456 789ss";
	//char dest1[8];
	size_t n = 8;
	ft_memmove(src + 5, src, n);
	ft_memmove(src1 + 5, src1, n);
	ft_putstr(src);
	ft_putstr("\n");
	ft_putstr(src1);
	return (0);
} */