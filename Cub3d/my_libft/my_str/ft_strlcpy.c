/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:08:38 by alborghi          #+#    #+#             */
/*   Updated: 2024/11/18 15:56:59 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size > 0)
	{
		i = 0;
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

/* int main()
{
	char src[] = "Hello, World!";
	char dest[5];
	char src1[] = "Hello, World!";
	char dest1[5];
	size_t n = 5;
	size_t ret;
	size_t ret1;

	ret = ft_strlcpy(dest, src, n);
	printf("dest: %s\n", dest);
	printf("ret: %zu\n", ret);
	ret1 = strlcpy(dest1, src1, n);
	printf("dest1: %s\n", dest1);
	printf("ret1: %zu\n", ret1);
	return (0);
} */