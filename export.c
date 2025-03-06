/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:01:27 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/06 16:13:00 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *  write(1, "\"", 1);
 *  write(1, &tmp->var[i], ft_strlen(&tmp->var[i]));
 *  write(1, "\"", 1);
 */
void	ft_put_export(t_env *env)
{
	int		i;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		i = 0;
		while (tmp->var[i] && tmp->var[i] != '=')
			i++;
		if (tmp->var[i] == '=')
			i++;
		write(1, "declare -x ", 11);
		write(1, tmp->var, i);
		if (tmp->var[i])
			ft_printf("\"%s\"", &tmp->var[i]);
		else if (tmp->var[i - 1] == '=')
			write(1, "\"\"", 2);
		write(1, "\n", 1);
		tmp = tmp->next;
	}
}

int	substitute_env_var(char *var, char *arg)
{
	if (ft_strchr(arg, '=') == NULL)
		return (0);
	free(var);
	var = ft_strdup(arg);
	if (!var)
		return (1);
	return (0);
}

int	append_env_var(t_env *last, char *arg, int is_env)
{
	last->next = (t_env *)malloc(sizeof(t_env));
	if (!last->next)
		return (1);
	last->next->var = ft_strdup(arg);
	if (!last->next->var)
		return (1);
	last->next->is_env = is_env;
	last->next->next = NULL;
	return (0);
}

//TODO: add free were needed
//TODO: add arg error handling
//TODO: add export += arg case
int	export_cmd(char *arg, t_env *env)
{
	t_env	*tmp;
	int		is_env;

	is_env = TRUE;
	if (ft_strchr(arg, '=') == NULL)
		is_env = FALSE;
	tmp = env;
	while (tmp)
	{
		if (check_key(tmp->var, arg) == TRUE)
		{
			if (substitute_env_var(tmp->var, arg) == 1)
				return (1);
			tmp->is_env = is_env;
			return (0);
		}
		if (!tmp->next)
			return (append_env_var(tmp, arg, is_env));
		tmp = tmp->next;
	}
	return (0);
}

int	check_arg(char *arg, char *cmd)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[0]) == 1)
	{
		ft_printf("minishell: %s: `%s': not a valid identifier\n", cmd, arg);
		return (1);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			ft_printf("minishell: %s: `%s': not a valid identifier\n", cmd,
						arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	exec_export(t_cmd *cmds, t_env *env)
{
	int		i;

	if (!cmds->args || !cmds->args[0])
		return (ft_put_export(env), 0);
	i = 0;
	while (cmds->args[i])
	{
		if (check_arg(cmds->args[i], "export") == 1)
			return (1);
		if (export_cmd(cmds->args[i], env) == 1)
			return (1);
		i++;
	}
	return (0);
}
