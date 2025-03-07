/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:44 by fre007            #+#    #+#             */
/*   Updated: 2025/03/07 11:08:26 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

//funzione per interrompere tutto il programma freeando tutto
void	ft_exit(t_data *data, int sig)
{
	free_cmds(data->head);
	free_env(data->env);
	free(data->home);
	free(data->pwd);
	free(data->oldpwd);
	close(data->stdi);
	close(data->stdo);
	close(data->prompt);
	close(0);
	close(1);
	exit(sig);
}
