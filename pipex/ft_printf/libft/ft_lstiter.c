/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:54:11 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/20 10:54:48 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	temp = (t_list *)lst;
	if (lst && f)
	{
		while (temp != NULL)
		{
			f(temp->content);
			temp = temp->next;
		}
	}
}
/* void print_content(void *content)
{
    printf("%d ", *((int *)content));
}

t_list *create_node(int value)
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
    t_list *list = create_node(1);
    t_list *second = create_node(2);
    t_list *third = create_node(3);
    
    list->next = second;
    second->next = third;

    ft_lstiter(list, print_content); // Should print: 1 2 3

    free(list->content);
    free(list);
    free(second->content);
    free(second);
    free(third->content);
    free(third);

    return 0;
} */