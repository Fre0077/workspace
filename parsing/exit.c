/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:44 by fre007            #+#    #+#             */
/*   Updated: 2025/02/20 20:12:44 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_words(t_words *words)
{
	t_words	*tmp;

	while (words != NULL)
	{
		tmp = words;
		words = words->next;
		free (tmp->word);
		free(tmp);
	}
}

void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;

	while (cmds != NULL)
	{
		tmp = cmds;
		free(cmds->cmd);
		ft_free_mat_char(cmds->args);
		cmds = cmds->next;
		free(tmp);
	}
}

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
void	ft_exit(t_data *data)
{
	free_cmds(data->cmds);
	free_env(data->env);
	free(data->home);
	free(data->pwd);
	free(data->oldpwd);
	close(data->stdi);
	close(data->stdo);
	exit(0);
}
