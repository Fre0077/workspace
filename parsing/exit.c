/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:44 by fre007            #+#    #+#             */
/*   Updated: 2025/03/07 09:10:55 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//se i file di input in data non sono vuoti li freea
void	free_input_data_file(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds->file_i[i] != NULL)
	{
		while (cmds->file_i[i] != NULL)
			free (cmds->file_i[i++]);
		free (cmds->file_i);
	}
	i = 0;
	if (cmds->delimiter != NULL)
	{
		while (cmds->delimiter[i] != NULL)
			free (cmds->delimiter[i++]);
		free (cmds->delimiter);
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
