/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:33:40 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 17:58:32 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*calc_hexa(unsigned int n)
{
	char	*str;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	i = ft_ulog(n, 16);
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (n > 0)
	{
		str[i] = HEX[n % 16];
		n /= 16;
		i--;
	}
	return (str);
}

void	ft_strtoupper(char *str)
{
	while (*str)
	{
		if (*str >= 'a' && *str <= 'z')
			*str -= 32;
		str++;
	}
}

static void	ft_strjoin_free_second(char *str, char **s2)
{
	char	*tmp;

	tmp = *s2;
	*s2 = ft_strjoin(str, *s2);
	free(tmp);
}

char	*handle_padding(t_params *flags, char *str, long int n)
{
	if (flags->flags[zero_padding] == '0'
		&& flags->flags[precision] != '.' && flags->flags[left_justify] != '-')
	{
		if (flags->flags[hex_form] == '#' && n != 0)
			flags->width -= 2;
		str = ft_pend_char(str, flags->width - ft_strlen_int(str), '0', 0);
		if (flags->flags[hex_form] == '#' && n != 0)
			ft_strjoin_free_second("0x", &str);
	}
	else
	{
		if (flags->flags[hex_form] == '#' && n != 0)
			ft_strjoin_free_second("0x", &str);
		str = ft_pend_char(str, flags->width - ft_strlen_int(str), ' ',
				flags->flags[left_justify] == '-');
	}
	return (str);
}

int	print_hexa(long int n, char opt, t_params *flags)
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
	ft_putstr_fd(str, 1);
	len = ft_strlen_int(str);
	free(str);
	return (len);
}
