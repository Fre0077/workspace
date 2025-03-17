/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:15 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 10:10:42 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_include.h"

int	print_char_flags(int c, t_params *flags)
{
	int	count;

	count = 0;
	if (flags->flags[left_justify] == '-')
	{
		count += ft_putchar_fd(c, 1);
		while (flags->width-- > 1)
			count += ft_putchar_fd(' ', 1);
	}
	else
	{
		while (flags->width-- > 1)
			count += ft_putchar_fd(' ', 1);
		count += ft_putchar_fd(c, 1);
	}
	return (count);
}
