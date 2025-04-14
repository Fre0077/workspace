/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:33:40 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 14:02:31 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hexa_e(long int n, char opt, t_params *flags)
{
	char			*str;
	int				len;

	str = calc_hexa(n);
	if (!str)
		return (0);
	if (flags->flags[precision] == '.')
		str = ft_pend_char(str, flags->precision - ft_strlen_int(str), '0', 0);
	str = handle_padding(flags, str, n);
	if (opt == 'X')
		ft_strtoupper(str);
	ft_putstr_fd(str, 2);
	len = ft_strlen_int(str);
	free(str);
	return (len);
}
