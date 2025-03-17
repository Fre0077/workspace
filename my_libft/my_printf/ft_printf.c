/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:17:46 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 17:58:57 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_allowed_flags(char *flags, char *allowed)
{
	int	i;

	if (!flags)
		return (1);
	if (!allowed)
		return (0);
	i = 0;
	while (flags[i])
	{
		if (!ft_strchr(allowed, flags[i]) && flags[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	add_flag(const char *str, int *i, t_params *flags)
{
	if (str[*i] == '-' && flags->flags[left_justify] != '-')
		flags->flags[left_justify] = '-';
	else if (str[*i] == '+' && flags->flags[force_sign] != '+')
		flags->flags[force_sign] = '+';
	else if (str[*i] == '0' && flags->flags[zero_padding] != '0')
		flags->flags[zero_padding] = '0';
	else if (str[*i] == '#' && flags->flags[hex_form] != '#')
		flags->flags[hex_form] = '#';
	else if (str[*i] == ' ' && flags->flags[no_sign] != ' ')
		flags->flags[no_sign] = ' ';
	else if (str[*i] == '.' && flags->flags[precision] != '.')
		flags->flags[precision] = '.';
	else
		return (-1);
	return (0);
}

static void	init_params(t_params *flags)
{
	ft_bzero(flags->flags, 8);
	ft_memset(flags->flags, '1', 7);
	flags->width = -1;
	flags->precision = -1;
}

int	handle_param(const char *str, int *i, va_list args)
{
	int			count;
	t_params	flags;

	(*i)++;
	count = 0;
	init_params(&flags);
	if (handle_flags2(str, i, &flags) == -1)
		return (-1);
	if (str[*i] == 'c')
		count = print_char_flags(va_arg(args, int), &flags);
	else if (str[*i] == 's')
		count = print_str(va_arg(args, char *), &flags);
	else if (str[*i] == 'd' || str[*i] == 'i')
		count = print_int(va_arg(args, int), &flags);
	else if (str[*i] == 'u')
		count = print_u_int(va_arg(args, unsigned long int), &flags);
	else if (str[*i] == 'x' || str[*i] == 'X')
		count = print_hexa(va_arg(args, int), str[*i], &flags);
	else if (str[*i] == 'p')
		count = print_void(va_arg(args, void *), &flags);
	else if (str[*i] == '%')
		count = ft_putchar('%');
	else
		count = -1;
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		count;
	int		ret;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		ret = 0;
		if (str[i] == '%')
			ret = handle_param(str, &i, args);
		else
			ret = ft_putchar(str[i]);
		if (ret == -1)
			return (-1);
		else
			count += ret;
		i++;
	}
	va_end(args);
	return (count);
}
