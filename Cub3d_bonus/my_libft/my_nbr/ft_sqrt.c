/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:16:32 by marvin            #+#    #+#             */
/*   Updated: 2024/11/30 10:16:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_sqrt(int nb)
{
	int	res;

	res = 0;
	if (nb < 0)
		return (0);
	while (res * res < nb)
		res++;
	if (res * res == nb)
		return (res);
	return (res - 1);
}

unsigned int	ft_usqrt(unsigned int nb)
{
	unsigned int	res;

	res = 0;
	while (res * res < nb)
		res++;
	if (res * res == nb)
		return (res);
	return (res - 1);
}

size_t	ft_stsqrt(size_t nb)
{
	size_t	res;

	res = 0;
	while (res * res < nb)
		res++;
	if (res * res == nb)
		return (res);
	return (res - 1);
}

long	ft_lsqrt(long nb)
{
	long	res;

	res = 0;
	while (res * res < nb)
		res++;
	if (res * res == nb)
		return (res);
	return (res - 1);
}
