/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:57:30 by alborghi          #+#    #+#             */
/*   Updated: 2024/11/19 16:57:55 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
	*lst = NULL;
}

/* int main()
{
	t_list	*list;
	t_list	*tmp;
	int i = 0;

	while (i < 10)
	{
		ft_lstadd_back(&list, ft_lstnew(ft_itoa(i)));
		i++;
	}
	i = 0;
	tmp = list;
	while (i < 5)
	{
		tmp = tmp->next;
	}
	ft_lstclear(&tmp, delete_node);
	if (list != NULL)
		return 1;
	printf("%s\n", (char *)(list->content));
	return 0;
} */