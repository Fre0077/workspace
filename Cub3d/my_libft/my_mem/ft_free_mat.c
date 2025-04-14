/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:15:21 by marvin            #+#    #+#             */
/*   Updated: 2024/11/30 10:15:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_mat(void **mat)
{
	size_t	i;

	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
	return (NULL);
}

void	*ft_free_mat_char(char **mat)
{
	int	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (mat && mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
	return (NULL);
}
