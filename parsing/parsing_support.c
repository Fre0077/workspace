/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_support.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:17:51 by fre007            #+#    #+#             */
/*   Updated: 2025/03/07 12:05:32 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//se stai veramente leggendo questa descrizione ho paura il il tuo QI
int	count_args(t_words **words)
{
	t_words	*tmp;
	int		i;

	(*words) = (*words)->next;
	tmp = *words;
	i = -1;
	while (++i + 1 && tmp != NULL && tmp->pipe == 0)
		tmp = tmp->next;
	return (i);
}

//freea solo i puntatori della lista word
void	free_words_only_pointers(t_words *words)
{
	t_words	*tmp;

	while (words != NULL)
	{
		tmp = words;
		words = words->next;
		free(tmp);
	}
}
