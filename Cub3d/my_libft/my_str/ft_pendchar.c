/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pendchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:20:11 by alborghi          #+#    #+#             */
/*   Updated: 2024/12/05 12:28:20 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../my_headers/libft.h"

/*
Append char: pass a number other than 0 (!= 0)
Prepend char: pass a number equal to 0 (== 0)
*/
char	*ft_pend_char(char *str, int n, char c, int append)
{
	char	*new;
	char	*tmp;

	if (n <= 0)
		return (str);
	tmp = ft_calloc(n + 1, sizeof(char));
	ft_memset(tmp, c, n);
	if (append != 0)
		new = ft_strjoin(str, tmp);
	else
		new = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
	return (new);
}
