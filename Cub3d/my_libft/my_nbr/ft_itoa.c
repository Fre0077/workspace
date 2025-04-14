/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:53:59 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 15:04:13 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_headers/libft.h"

static void	calculations(int n, int div, int i, char **str)
{
	while (div)
	{
		(*str)[i] = n / div + '0';
		n %= div;
		div /= 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	int		div;
	char	*str;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	div = 1;
	while (n / div >= 10 || n / div <= -10)
		div *= 10;
	str = (char *)ft_calloc(ft_log(ft_abs(n), 10) + 1 + (n < 0), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
		i++;
	}
	calculations(n, div, i, &str);
	return (str);
}
