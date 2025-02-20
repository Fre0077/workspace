/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:25:48 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 10:22:12 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = (t_list *)*lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

/* // Funzione per stampare la lista
void print_list(t_list *lst)
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

	ft_lstadd_back(&new, sec);
	
	print_list(new);
	printf("\n");
	
	ft_lstadd_back(&new, ter);
	
	print_list(new);
	printf("\n");
} */