/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:01:52 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/21 10:29:26 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int				len;
	unsigned int	num;

	len = 1;
	num = n;
	if (n < 0)
	{
		num = -n;
		len++;
	}
	while (num > 9)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	num;
	char			*str;

	len = num_len(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	num = n;
	if (n < 0)
	{
		str[0] = '-';
		num = -n;
	}
	str[len] = '\0';
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[--len] = (num % 10) + 48;
		num /= 10;
	}
	return (str);
}

/* int main() {
	int	i;
	
	i = 7;
    int numbers[] = {123, -123, 0, 98765, -98765, 2147483647, -2147483648};
    while (--i >= 0)
	{
		printf("result: %s\n", ft_itoa(numbers[i]));
		printf("num: %d\n\n", numbers[i]);
	}
} */