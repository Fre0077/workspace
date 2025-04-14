/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:33:04 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 17:58:43 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_no_sign(int n)
{
	if (n == -2147483648)
		return (ft_strdup("2147483648"));
	else
		return (ft_itoa(ft_abs(n)));
}

static void	do_sign_checks(t_params *flags, char **nbr, int n)
{
	if (n < 0)
		*nbr = ft_pend_char(*nbr, 1, '-', 0);
	else if (flags->flags[force_sign] == '+')
		*nbr = ft_pend_char(*nbr, 1, '+', 0);
	else if (flags->flags[no_sign] == ' ')
		*nbr = ft_pend_char(*nbr, 1, ' ', 0);
}

int	print_int(int n, t_params *flags)
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
	ft_putstr_fd(nbr, 1);
	len = (int)ft_strlen(nbr);
	return (free(nbr), len);
}

char	*ft_utoa(unsigned int n)
{
	char			*str;
	int				i;

	if (n == 0)
		return (ft_strdup("0"));
	i = ft_ulog(n, 10);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (str);
}

int	print_u_int(unsigned int n, t_params *flags)
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
	ft_putstr_fd(nbr, 1);
	len = (int)ft_strlen(nbr);
	return (free(nbr), len);
}
