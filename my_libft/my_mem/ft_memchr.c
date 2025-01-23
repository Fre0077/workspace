/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:50:16 by alborghi          #+#    #+#             */
/*   Updated: 2024/11/20 09:52:40 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ret;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
		{
			ret = (unsigned char *)s + i;
			return (ret);
		}
		i++;
	}
	return (NULL);
}

/* int main()
{
	char str[] = "Hello World!";
	char *ptr;
	char *ptr2;
	char c = 'l';
	ptr = ft_memchr(str, c, 12);
	printf("String after %c is %s\n", c, ptr);
	ptr2 = memchr(str, c, 12);
	printf("String after %c is %s\n", c, ptr2);
	return 0;
} */