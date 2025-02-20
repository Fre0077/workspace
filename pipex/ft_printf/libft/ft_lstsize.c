/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:14:07 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 11:09:02 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp_list;

	i = 0;
	temp_list = (t_list *)lst;
	while (temp_list != NULL)
	{
		i++;
		temp_list = temp_list->next;
	}
	return (i);
}
