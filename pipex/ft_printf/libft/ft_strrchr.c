/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:02:55 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 22:23:31 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
	while (str[++i])
	{
		if (str[i] == (char)c)
			temp = (char *)&str[i];
	}
	if (c == '\0')
		return ((char *)&str[i]);
	return (temp);
}

/* int main()
{
	printf("%s", strrchr("", '\0'));
} */