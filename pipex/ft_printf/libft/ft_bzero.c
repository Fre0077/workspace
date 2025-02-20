/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:43:08 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/23 18:50:38 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *buffer, size_t count)
{
	char	*str;
	size_t	i;

	if (!buffer)
		return (NULL);
	str = (char *)buffer;
	i = 0;
	while (i < count)
		str[i++] = 0;
	return (buffer);
}
/* int main()
{
    char buffer[10] = "123456789";
    printf("Prima di ft_bzero: \"%s\"\n", buffer);

    ft_bzero(buffer, 5);
    printf("Dopo ft_bzero (5 byte): \"%s\"\n", buffer);

    char buffer2[10] = "abcdefghi";
    printf("Prima di bzero (standard): \"%s\"\n", buffer2);
    bzero(buffer2, 5);
    printf("Dopo bzero (5 byte): \"%s\"\n", buffer2);
} */
