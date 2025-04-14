/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printe.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:14:48 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/21 11:15:01 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTE_H
# define FT_PRINTE_H

# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

// ft_printf_bonus.c
int		handle_param_e(const char *str, int *i, va_list args);
int		ft_printe(const char *str, ...);

// ft_parsing_bonus.c
int		handle_flags2(const char *str, int *i, t_params *flags);

// ft_char_bonus.c
int		print_char_flags_e(int c, t_params *flags);

// ft_hexa.c
int		print_hexa_e(long int n, char opt, t_params *flags);

// ft_void.c
int		print_void_e(void *ptr, t_params *flags);

// ft_nbrs.c
int		print_int_e(int n, t_params *flags);
int		print_u_int_e(unsigned int n, t_params *flags);

// ft_strs.c
int		print_str_e(char *s, t_params *flags);

#endif