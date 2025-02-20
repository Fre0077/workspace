/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:48:37 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/23 20:52:53 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*str;

	if (!s || !f)
		return (NULL);
	i = -1;
	len = ft_strlen(s);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (++i < len)
		str[i] = f(i, s[i]);
	return (str);
}

/* char to_Upper(unsigned int index, char c) {
    if (index % 2 == 0)
        return (char)(c - 32);
    return c;
}

int main()
{
	printf("%s\n", ft_strmapi("hello world", to_Upper));
} */