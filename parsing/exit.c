/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:44 by fre007            #+#    #+#             */
/*   Updated: 2025/02/20 16:12:33 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_words(t_words *words)
{
	while (words != NULL)
	{
		free (words->word);
		words = words->next;
	}
	free (words);
}

void	free_cmds(t_cmd *cmds)
{
	
	t_cmd	*tmp;
	int	i;

	i = 0;
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
	exit(0);
}
