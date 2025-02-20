/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:22:19 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 22:43:09 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

/* t_list *create_node(int value)
{
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return NULL;
    new_node->content = malloc(sizeof(int));
    if (!new_node->content)
    {
        free(new_node);
        return NULL;
    }
    *((int *)new_node->content) = value;
    new_node->next = NULL;
    return new_node;
}

int main(void)
{
    t_list *list = create_node(49);
    t_list *second = create_node(50);
    t_list *third = create_node(51);
    
    list->next = second;
    second->next = third;

	t_list *last = ft_lstlast(list);
    printf("%s\n", (char *)last->content);
} */