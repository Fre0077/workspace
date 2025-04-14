/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:34:23 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 17:58:21 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	digit_flag(char *str_flag, int j, t_params *flags)
{
	if (flags->flags[precision] == '.')
	{
		flags->precision = ft_atoi(&str_flag[j]);
		j += ft_log(flags->precision, 10);
	}
	else if (flags->flags[width] != 'w')
	{
		flags->flags[width] = 'w';
		flags->width = ft_atoi(&str_flag[j]);
		j += ft_log(flags->width, 10);
	}
	return (j);
}

int	char_flag(char *str_flag, int j, t_params *flags)
{
	if (add_flag(str_flag, &j, flags) == -1)
	{
		free(str_flag);
		return (-1);
	}
	j++;
	return (j);
}

int	handle_flags(const char *str, int *i, t_params *flags)
{
	char	*str_flag;
	int		j;

	str_flag = str_dup_till_charset(&str[*i], SPEC);
	if (!str_flag)
		return (-1);
	j = 0;
	while (str_flag[j])
	{
		if (ft_isdigit(str_flag[j]) && (str_flag[j] != '0'
				|| flags->flags[zero_padding] == '0'))
		{
			j = digit_flag(str_flag, j, flags);
		}
		else if (ft_strchr(FLAGS, str_flag[j]))
		{
			j = char_flag(str_flag, j, flags);
		}
		else
			return (-1);
	}
	*i += j;
	free(str_flag);
	return (0);
}
