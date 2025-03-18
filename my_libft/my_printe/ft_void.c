/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_void.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:07:58 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 13:59:57 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_ullog(unsigned long n, int base)
{
	int	count;

	count = 0;
	while (n > 0)
	{
		n /= base;
		count++;
	}
	return (count);
}

static char	*calc_void(unsigned long n)
{
	char	*str;
	int		i;

	if (n == 0)
		return (ft_strdup("0"));
	i = ft_ullog(n, 16);
	str = (char *)malloc(i + 1);
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

static void	ft_strjoin_free_first(char **str, char *s2)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, s2);
	free(tmp);
}

int	print_void_e(void *ptr, t_params *flags)
{
	int		len;
	char	*str;
	char	*addr;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	str = calc_void((unsigned long)ptr);
	if (!str)
		return (0);
	addr = ft_strdup("0x");
	if (flags->flags[zero_padding] == '0' && flags->flags[left_justify] != '-')
		addr = ft_pend_char(addr, flags->width - (int)ft_strlen(addr), '0', 1);
	if (flags->flags[left_justify] != '-')
		addr = ft_pend_char(addr, flags->width - (int)ft_strlen(addr), ' ', 0);
	ft_strjoin_free_first(&addr, str);
	free(str);
	if (flags->flags[left_justify] == '-')
		addr = ft_pend_char(addr, flags->width - (int)ft_strlen(addr), ' ', 1);
	len = (int)ft_strlen(addr);
	ft_putstr_fd(addr, 2);
	free(addr);
	return (len);
}
