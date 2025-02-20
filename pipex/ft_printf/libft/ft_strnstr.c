/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:27:12 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/21 10:26:56 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	char	*haystack;
	size_t	letters_left;
	size_t	needle_len;

	if (needle[0] == '\0')
		return ((char *)hay);
	haystack = (char *)hay;
	letters_left = len;
	needle_len = (size_t)ft_strlen(needle);
	while (*haystack && letters_left-- >= needle_len)
	{
		if (*haystack == *needle)
			if (ft_strncmp((char *)needle, haystack, needle_len) == 0)
				return (haystack);
		haystack++;
	}
	return (NULL);
}
/* int main    ()
{
	printf("%s\n", ft_strnstr("come va", "", 11));
} */
	/* if (!hay || !needle)
		return (NULL); */