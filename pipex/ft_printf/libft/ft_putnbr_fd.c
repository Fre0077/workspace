/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:38 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/29 07:40:35 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int		i;
	int		len;
	char	num[10];

	i = 0;
	len = 0;
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11), 11);
	if (n < 0)
	{
		n = -n;
		len++;
		write(fd, "-", 1);
	}
	while (n >= 10)
	{
		num[i++] = (n % 10) + '0';
		n = n / 10;
	}
	num[i] = (n % 10) + '0';
	len = len + i + 1;
	while (i >= 0)
		write(fd, &num[i--], 1);
	return (len);
}
