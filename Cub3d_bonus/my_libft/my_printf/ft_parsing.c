/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:17:11 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 17:58:49 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_precision(char *str_flag, int *j, t_params *flags)
{
	(*j)++;
	flags->flags[precision] = '.';
	flags->precision = ft_atoi(&str_flag[*j]);
	*j += ft_ulog(flags->precision, 10);
}

static void	set_width(char *str_flag, int *j, t_params *flags)
{
	flags->width = ft_atoi(&str_flag[*j]);
	*j += ft_ulog(flags->width, 10);
}

int	handle_flags2(const char *str, int *i, t_params *flags)
{
	char	*str_flag;
	int		j;

	str_flag = str_dup_till_charset(&str[*i], SPEC);
	if (!str_flag)
		return (-1);
	j = 0;
	while (str_flag[j] && ft_strchr("0-+# ", str_flag[j]))
	{
		if (add_flag(str_flag, &j, flags) == -1)
		{
			free(str_flag);
			return (-1);
		}
		j++;
	}
	if (ft_isdigit(str_flag[j]))
		set_width(str_flag, &j, flags);
	if (str_flag[j] == '.')
		set_precision(str_flag, &j, flags);
	*i += j;
	free(str_flag);
	return (0);
}
