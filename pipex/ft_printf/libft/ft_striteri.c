/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:08:53 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 22:13:52 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = -1;
	while (s[++i])
		f(i, &s[i]);
}

/* void	to_Upper(unsigned int index, char *c) {
    if (c[index] >= 'a' && c[index] <= 'z')
		c[index] -= 32;
}

int main()
{
	char s[13] = "hello world";
	ft_striteri(s, to_Upper);
	printf("%s\n", s);
} */