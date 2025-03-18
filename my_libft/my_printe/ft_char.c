/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:00:15 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 13:54:58 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_include.h"

int	print_char_flags_e(int c, t_params *flags)
{
	int	count;

	count = 0;
	if (flags->flags[left_justify] == '-')
	{
		count += ft_putchar_fd(c, 2);
		while (flags->width-- > 1)
			count += ft_putchar_fd(' ', 2);
	}
	else
	{
		while (flags->width-- > 1)
			count += ft_putchar_fd(' ', 2);
		count += ft_putchar_fd(c, 2);
	}
	return (count);
}
