/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:17:46 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 14:23:28 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_headers/ft_printe.h"

static void	init_params(t_params *flags)
{
	ft_bzero(flags->flags, 8);
	ft_memset(flags->flags, '1', 7);
	flags->width = -1;
	flags->precision = -1;
}

int	handle_param_e(const char *str, int *i, va_list args)
{
	int			count;
	t_params	flags;

	(*i)++;
	count = 0;
	init_params(&flags);
	if (handle_flags2(str, i, &flags) == -1)
		return (-1);
	if (str[*i] == 'c')
		count = print_char_flags_e(va_arg(args, int), &flags);
	else if (str[*i] == 's')
		count = print_str_e(va_arg(args, char *), &flags);
	else if (str[*i] == 'd' || str[*i] == 'i')
		count = print_int_e(va_arg(args, int), &flags);
	else if (str[*i] == 'u')
		count = print_u_int_e(va_arg(args, unsigned long int), &flags);
	else if (str[*i] == 'x' || str[*i] == 'X')
		count = print_hexa_e(va_arg(args, int), str[*i], &flags);
	else if (str[*i] == 'p')
		count = print_void_e(va_arg(args, void *), &flags);
	else if (str[*i] == '%')
		count = ft_putchar_fd('%', 2);
	else
		count = -1;
	return (count);
}

int	ft_printe(const char *str, ...)
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
			ret = handle_param_e(str, &i, args);
		else
			ret = ft_putchar_fd(str[i], 2);
		if (ret == -1)
			return (-1);
		else
			count += ret;
		i++;
	}
	va_end(args);
	return (count);
}
