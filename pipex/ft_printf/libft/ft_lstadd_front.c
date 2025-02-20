/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:48:11 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 10:28:18 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/* void print_list(t_list *lst)
{
    while (lst->next != NULL)
    {
        printf("content -> %s", (char *)lst->content);
		printf("\n");
		printf("next -> %p", lst->next);
		printf("\n");
        lst = lst->next;
    }
	printf("content -> %s", (char *)lst->content);
	printf("\n");
	printf("next -> %p", lst->next);
	printf("\n");
}

int main()
{
	t_list *new = ft_lstnew("ciao");
	t_list *sec = ft_lstnew("come");
	t_list *ter = ft_lstnew("va");

	print_list(new);
	printf("\n\n");

	ft_lstadd_front(&new, sec);
	
	print_list(new);
	printf("\n");
	
	ft_lstadd_front(&new, ter);
	
	print_list(new);
	printf("\n");
}  */