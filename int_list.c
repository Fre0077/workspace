/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:15:30 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 16:03:42 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_int_list	*new_int_list(int n)
{
	t_int_list	*new;

	new = (t_int_list *)malloc(sizeof(t_int_list));
	if (!new)
		return (NULL);
	new->n = n;
	new->next = NULL;
	return (new);
}

t_int_list	*add_int_list(t_int_list *list, int n)
{
	t_int_list	*tmp;

	if (!list)
		return (new_int_list(n));
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_int_list(n);
	if (!tmp->next)
		return (free_int_list(list), NULL);
	return (list);
}

t_int_list	*remove_node(t_int_list *list)
{
	t_int_list	*tmp;

	if (!list)
		return (NULL);
	tmp = list->next;
	free(list);
	return (tmp);
}

void	free_int_list(t_int_list *list)
{
	t_int_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void	close_fds(t_int_list *fds)
{
	t_int_list	*tmp;

	while (fds)
	{
		tmp = fds;
		fds = fds->next;
		close(tmp->n);
		free(tmp);
	}
}
