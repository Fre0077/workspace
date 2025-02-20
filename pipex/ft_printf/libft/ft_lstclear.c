/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:04:48 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 22:47:13 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void	*))
{
	t_list	*temp;
	t_list	*next;

	temp = *lst;
	if (del && lst && *lst)
	{
		while (temp != NULL)
		{
			next = temp->next;
			del(temp->content);
			free(temp);
			temp = next;
		}
		*lst = NULL;
	}
}

/* void del(void *)
{
	
}

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

	ft_lstadd_front(&new, sec);
	
	print_list(new);
	printf("\n");
	
	ft_lstadd_front(&new, ter);
	
	print_list(new);
	printf("\n");
}  */