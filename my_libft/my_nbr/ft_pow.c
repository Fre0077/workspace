/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:00:43 by marvin            #+#    #+#             */
/*   Updated: 2024/11/30 10:00:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int nb, int power)
{
	int	res;

	res = 1;
	if (power < 0)
		return (0);
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	return (res);
}

unsigned int	ft_upow(unsigned int nb, unsigned int power)
{
	unsigned int	res;

	res = 1;
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	return (res);
}

size_t	ft_stpow(size_t nb, size_t power)
{
	size_t	res;

	res = 1;
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	return (res);
}

long	ft_lpow(long nb, long power)
{
	long	res;

	res = 1;
	while (power > 0)
	{
		res *= nb;
		power--;
	}
	return (res);
}
