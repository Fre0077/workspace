/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:44 by fre007            #+#    #+#             */
/*   Updated: 2025/02/20 12:46:29 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//libera la lista che contine le parole suddivise ed elaborate
void	free_words(t_words *words)
{
	while (words != NULL)
	{
		free (words->word);
		words = words->next;
	}
	free (words);
}

//funzione per interrompere tutto il programma freeando tutto
void	ft_exit(t_data *data)
{
	(void)data;
}