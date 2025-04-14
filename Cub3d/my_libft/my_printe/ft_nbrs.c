/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:33:04 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 13:57:18 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_include.h"

static void	do_sign_checks(t_params *flags, char **nbr, int n)
{
	if (n < 0)
		*nbr = ft_pend_char(*nbr, 1, '-', 0);
	else if (flags->flags[force_sign] == '+')
		*nbr = ft_pend_char(*nbr, 1, '+', 0);
	else if (flags->flags[no_sign] == ' ')
		*nbr = ft_pend_char(*nbr, 1, ' ', 0);
}

int	print_int_e(int n, t_params *flags)
{
	char	*nbr;
	int		len;
	int		sign;

	nbr = ft_itoa_no_sign(n);
	sign = 0;
	if (n < 0 || flags->flags[force_sign] == '+'
		|| flags->flags[no_sign] == ' ')
		sign = 1;
	if (flags->flags[precision] == '.')
		nbr = ft_pend_char(nbr, flags->precision - ft_strlen_int(nbr), '0', 0);
	if (flags->flags[zero_padding] == '0' && flags->flags[precision] != '.'
		&& flags->flags[left_justify] != '-')
		nbr = ft_pend_char(nbr,
				flags->width - ft_strlen_int(nbr) - sign, '0', 0);
	do_sign_checks(flags, &nbr, n);
	if (flags->flags[left_justify] == '-')
		nbr = ft_pend_char(nbr, flags->width - ft_strlen_int(nbr), ' ', 1);
	else
		nbr = ft_pend_char(nbr, flags->width - ft_strlen_int(nbr), ' ', 0);
	ft_putstr_fd(nbr, 2);
	len = (int)ft_strlen(nbr);
	return (free(nbr), len);
}

int	print_u_int_e(unsigned int n, t_params *flags)
{
	char	*nbr;
	int		len;
	int		sign;

	nbr = ft_utoa(n);
	sign = 0;
	if (flags->flags[force_sign] == '+' || flags->flags[no_sign] == ' ')
		sign = 1;
	if (flags->flags[precision] == '.')
		nbr = ft_pend_char(nbr, flags->precision - (int)ft_strlen(nbr), '0', 0);
	if (flags->flags[zero_padding] == '0' && flags->flags[precision] != '.'
		&& flags->flags[left_justify] != '-')
		nbr = ft_pend_char(nbr,
				flags->width - (int)ft_strlen(nbr) - sign, '0', 0);
	else if (flags->flags[force_sign] == '+')
		nbr = ft_pend_char(nbr, 1, '+', 0);
	else if (flags->flags[no_sign] == ' ')
		nbr = ft_pend_char(nbr, 1, ' ', 0);
	if (flags->flags[left_justify] == '-')
		nbr = ft_pend_char(nbr, flags->width - (int)ft_strlen(nbr), ' ', 1);
	else
		nbr = ft_pend_char(nbr, flags->width - (int)ft_strlen(nbr), ' ', 0);
	ft_putstr_fd(nbr, 2);
	len = (int)ft_strlen(nbr);
	return (free(nbr), len);
}
