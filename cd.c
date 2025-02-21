/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:52:08 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/21 14:31:44 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key(char *var, char *key)
{
	int	i;

	if (!var || !key)
		return (FALSE);
	i = 0;
	while (var[i] && key[i] && var[i] == key[i] && var[i] != '=')
		i++;
	if ((var[i] == '=' || var[i] == '\0') && (key[i] == '\0' || key[i] == '='))
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

	if (!env || !key || !value)
		return (1);
	tmp = env;
	while (tmp)
	{
		if (check_key(tmp->var, key) == TRUE)
		{
			free(tmp->var);
			tmp->var = ft_strjoin_free_1_2(ft_strjoin(key, "="), value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

/**
 * caso gestito
 * alborghi@c1r6p7:~$ cd
 * alborghi@c1r6p7:~$ unset HOME
 * alborghi@c1r6p7:/nfs/homes/alborghi$ cd ..
 * alborghi@c1r6p7:/nfs/homes$ cd
 * bash: cd: HOME not set
 * alborghi@c1r6p7:/nfs/homes$ cd ~
 * alborghi@c1r6p7:/nfs/homes/alborghi$ 
 */
//TODO: check if everything is freed correctly (spoiler: it's not)
int	exec_cd(t_data *data)
{
	char	*oldpwd;

	if (!data->cmds)
		return (1);
	if (ft_char_mat_len(data->cmds->args) > 1)
		return (printf("cd: too many arguments\n"), 1);
	oldpwd = getcwd(NULL, 0);
	if (!data->cmds->args || data->cmds->args[0] == NULL
		|| data->cmds->args[0][0] == '\0')
	{
		if (chdir(getenv("HOME")) == -1)
			printf("cd: HOME not set\n");
	}
	else if (ft_strncmp(data->cmds->args[0], "~", 2) == 0)
	{
		if (chdir(data->home) == -1)
		{
			printf("cd: %s: No such file or directory\n", data->home);
			return (1);
		}
	}
	else if (ft_strncmp(data->cmds->args[0], "-", 2) == 0)
	{
		if (get_env(data->env, "OLDPWD"))
		{
			if (chdir(get_env(data->env, "OLDPWD")) == -1)
			{
				printf("cd: %s No such file or directory\n", get_env(data->env, "OLDPWD"));
				return (1);
			}
		}
		else if (!data->oldpwd || chdir(data->oldpwd) == -1)
		{
			printf("cd: %s No such file or directory\n", data->oldpwd);
			return (1);
		}
	}
	else if (chdir(data->cmds->args[0]) == -1)
	{
		printf("cd: |%s| No such file or directory\n", data->cmds->args[0]);
		return (1);
	}
	if (get_env(data->env, "OLDPWD"))
	{
		free(data->oldpwd);
		data->oldpwd = ft_strdup(oldpwd);
		set_env(data->env, "OLDPWD", oldpwd);
	}
	else
	{
		free(data->oldpwd);
		data->oldpwd = ft_strdup(oldpwd);
		free(oldpwd);
	}
	if (get_env(data->env, "PWD"))
	{
		free(data->pwd);
		data->pwd = getcwd(NULL, 0);
		set_env(data->env, "PWD", getcwd(NULL, 0));
	}
	else
	{
		free(data->pwd);
		data->pwd = getcwd(NULL, 0);
	}
	return (0);
}
