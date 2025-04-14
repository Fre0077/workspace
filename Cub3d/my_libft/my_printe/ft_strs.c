/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:38:35 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 13:55:48 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_include.h"

static int	print_helper(char *to_print, t_params *flags, int len)
{
	if (flags->flags[left_justify] == '-')
	{
		ft_putstr_fd(to_print, 2);
		while (len < flags->width)
			len += ft_putchar(' ');
	}
	else
	{
		while (len < flags->width)
			len += ft_putchar(' ');
		ft_putstr_fd(to_print, 2);
	}
	return (len);
}

int	print_str_e(char *s, t_params *flags)
{
	char	*to_print;
	int		len;

	if (!s)
	{
		if (flags->precision >= 6 || flags->precision == -1)
		{
			ft_putstr_fd("(null)", 2);
			return (6);
		}
		return (0);
	}
	if (flags->precision == -1)
		to_print = ft_strdup(s);
	else
		to_print = ft_substr(s, 0, flags->precision);
	if (!to_print)
		return (-1);
	len = (int)ft_strlen(to_print);
	len = print_helper(to_print, flags, len);
	free(to_print);
	return (len);
}
