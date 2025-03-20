/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:52:08 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/20 10:13:09 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *var, char *key)
{
	int	i;

	if (!var || !key)
		return (FALSE);
	i = 0;
	while (var[i] && key[i] && var[i] == key[i] && var[i] != '='
			&& key[i] != '+')
		i++;
	if ((var[i] == '=' || var[i] == '\0' || var[i] == '+')
		&& (key[i] == '\0' || key[i] == '=' || key[i] == '+'))
		return (TRUE);
	return (FALSE);
}

char	*get_env(t_env *env, char *key)
{
	t_env	*tmp;

	if (!env || !key)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (check_key(tmp->var, key) == TRUE && tmp->is_env == TRUE)
			return (ft_strchr(tmp->var, '=') + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

int	set_env(t_env *env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*last;
	char	*tmp_var;

	if (!env || !key || !value)
		return (1);
	tmp = env;
	last = env;
	while (tmp)
	{
		if (check_key(tmp->var, key) == TRUE)
		{
			free(tmp->var);
			tmp->var = ft_strjoin_free_1_2(ft_strjoin(key, "="), value);
			return (0);
		}
		last = tmp;
		tmp = tmp->next;
	}
	tmp_var = ft_strjoin_free_1_2(ft_strjoin(key, "="),
							value);
	if (!tmp_var)
		return (1);
	append_env_var(last, tmp_var, TRUE);
	return (free(tmp_var), 1);
}

int	exec_cd(t_data *data)
{
	char	*oldpwd;
	char	*tmp;

	if (!data->cmds)
		return (1);
	if (ft_char_mat_len(data->cmds->args) > 1)
		return (ft_printe("cd: too many arguments\n"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!data->cmds->args || data->cmds->args[0] == NULL
		|| data->cmds->args[0][0] == '\0')
	{
		if (get_env(data->env, "HOME") == NULL
			|| chdir(get_env(data->env, "HOME")) == -1)
		{
			if (get_env(data->env, "HOME") == NULL)
				ft_printe("minishell: cd: HOME not set\n");
			else
			{
				tmp = ft_strjoin("minishell: cd: ", get_env(data->env, "HOME"));
				perror(tmp);
				free(tmp);
			}
			free(oldpwd);
			return (1);
		}
	}
	else if (ft_strncmp(data->cmds->args[0], "~/", 2) == 0
			|| ft_strncmp(data->cmds->args[0], "~", 2) == 0)
	{
		if (get_env(data->env, "HOME") != NULL)
			tmp = ft_strjoin(get_env(data->env, "HOME"),
						data->cmds->args[0] + 1);
		else
			tmp = ft_strjoin(data->home, data->cmds->args[0] + 1);
		if (chdir(tmp) == -1)
		{
			tmp = ft_strjoin_free_2("minishell: cd: ", tmp);
			perror(tmp);
			free(tmp);
			free(oldpwd);
			return (1);
		}
		free(tmp);
	}
	else if (ft_strncmp(data->cmds->args[0], "-", 2) == 0)
	{
		if (get_env(data->env, "OLDPWD"))
		{
			if (chdir(get_env(data->env, "OLDPWD")) == -1)
			{
				tmp = ft_strjoin("minishell: cd: ",
							get_env(data->env, "OLDPWD"));
				perror(tmp);
				free(tmp);
				free(oldpwd);
				return (1);
			}
			ft_printf("%s\n", get_env(data->env, "OLDPWD"));
		}
		else
		{
			ft_printe("minishell: cd: OLDPWD not set\n");
			free(oldpwd);
			return (1);
		}
	}
	else if (chdir(data->cmds->args[0]) == -1)
	{
		tmp = ft_strjoin("minishell: cd: ", data->cmds->args[0]);
		perror(tmp);
		free(tmp);
		free(oldpwd);
		return (1);
	}
	set_env(data->env, "OLDPWD", oldpwd);
	free(data->pwd);
	data->pwd = getcwd(NULL, 0);
	set_env(data->env, "PWD", getcwd(NULL, 0));
	return (0);
}
