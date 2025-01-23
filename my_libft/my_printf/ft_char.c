/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:15 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/06 14:23:15 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_include.h"

int	print_char_flags(int c, t_params *flags)
{
	int	count;

	count = 0;
	if (flags->flags[left_justify] == '-')
	{
		count += ft_putchar(c);
		while (flags->width-- > 1)
			count += ft_putchar(' ');
	}
	else
	{
		while (flags->width-- > 1)
			count += ft_putchar(' ');
		count += ft_putchar(c);
	}
	return (count);
}
