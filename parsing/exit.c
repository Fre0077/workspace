/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:44 by fre007            #+#    #+#             */
/*   Updated: 2025/03/19 11:32:03 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//freea le word della lista words
void	free_words_word(t_words *words)
{
	t_words	*tmp;

	while (words != NULL)
	{
		tmp = words;
		words = words->next;
		if (tmp->word != NULL)
			free(tmp->word);
		tmp->word = NULL;
	}
}

//freea la lista words
void	free_words(t_words *words)
{
	t_words	*tmp;

	while (words != NULL)
	{
		tmp = words;
		words = words->next;
		free(tmp->word);
		free(tmp);
	}
}

//freea la lista cmds
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds != NULL)
	{
		tmp = cmds;
		cmds = cmds->next;
		free(tmp->cmd);
		ft_free_mat_char(tmp->args);
		free(tmp->divider);
		free(tmp->file_o);
		free(tmp->file_a);
		ft_free_mat_char(tmp->file_i);
		ft_free_mat_char(tmp->delimiter);
		free(tmp);
	}
}

//freea l'env
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->var);
		free(tmp);
	}
}

// TODO: move "exit" printf here
/**
 * @brief funzione per interrompere tutto il programma freeando tutto
*/
void	ft_exit(t_data *data, int sig)
{
	free_cmds(data->head);
	free_env(data->env);
	free(data->home);
	free(data->pwd);
	close(data->stdi);
	close(data->stdo);
	close(data->prompt);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close_fds(data->fds);
	free_int_list(data->pids);
	exit(sig);
}
