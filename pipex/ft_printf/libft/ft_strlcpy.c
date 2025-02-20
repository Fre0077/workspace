/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:11:39 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/23 20:59:23 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (!src)
		return (0);
	if (size < 1 || !dest)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	i = 0;
	while (src[i])
		i++;
	return (i);
}

/* int	main(void)
{
	char	dest[70] = "cane e gatto";
	char	src[] = "07306802";
	int		count;

	count = ft_strlcpy(dest, src, 0);
	printf("%s\n", dest);
	printf("%s\n", src);
	printf("%d\n", count);
} */