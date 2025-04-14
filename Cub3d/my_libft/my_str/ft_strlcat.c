/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:44:15 by alborghi          #+#    #+#             */
/*   Updated: 2024/11/21 14:24:03 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (dest[j] != '\0')
		j++;
	if (j >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (i + j < size - 1 && src[i] != '\0')
	{
		dest[j + i] = src[i];
		i++;
	}
	dest[j + i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i + j);
}

/* int main()
{
	char dest[100] = "Hello";
	char src[100] = " World!";
	size_t size = 100;
	printf("ft_strlcat: %lu\n", ft_strlcat(dest, src, size));
	printf("dest: %s\n", dest);
	char dest2[100] = "Hello";
	char src2[100] = " World!";
	size_t size2 = 100;
	printf("strlcat: %lu\n", strlcat(dest2, src2, size2));
	printf("dest2: %s\n", dest2);
	return (0);
}
int main()
{
	char *dest;
	dest = (char *)malloc(15 * sizeof(char));
	dest[10] = 'a';
	ft_putnbr_fd(ft_strlcat(dest, "lorem ipsum dolor sit amet", 0), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd(dest, 1);
	free(dest);
	return (0);
} */