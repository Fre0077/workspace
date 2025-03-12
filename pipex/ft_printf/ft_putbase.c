/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:26:36 by ecarbona          #+#    #+#             */
/*   Updated: 2025/03/11 15:41:39 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putbase(unsigned long n, char *base)
{
	unsigned long	temp;
	char			*array;
	int				i;

	temp = n;
	i = 0;
	if (n == 0)
		return (write (1, "0", 1), 1);
	while (temp > 0)
	{
		temp /= 16;
		i++;
	}
	array = malloc(sizeof(char) * (i + 1));
	array[i] = '\0';
	while (n > 0)
	{
		array[--i] = base[n % 16];
		n = n / 16;
	}
	while (array[i])
		write (1, &array[i++], 1);
	return (free (array), i);
}
