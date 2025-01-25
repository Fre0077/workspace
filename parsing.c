/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:25:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/25 10:22:49 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_mark(t_marks *marks, char *c, int i)
{
	if (i != 0 && c[i - 1] == '\\')
		return (0);
	if (c[i] == '\'' && marks->_1 == 0 && marks->_2 == 0)
		return (marks->_1 = 1, 1);
	else if (c[i] == '"' && marks->_1 == 0 && marks->_2 == 0)
		return (marks->_2 = 1, 1);
	else if (c[i] == '\'' && marks->_1 == 1)
		return (marks->_1 = 0, 0);	
	else if (c[i] == '"' && marks->_2 == 1)
		return (marks->_2 = 0, 0);
	return (0);
}

int	count_arg(char *line)
{
	int		count;
	int		i;
	t_marks	marks;

	i = 0;
	count = 0;
	marks._1 = 0;
	marks._2 = 0;
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ' && marks._1 == 0 && marks._2 == 0)
			i++;
		if (check_mark(&marks, line, i))
			count++;
		else if (((line[i - 1] == ' ' && line[i])
			|| (line[i - 1] != ' ' && i == 0))
			&& marks._1 == 0 && marks._2 == 0)
			count++;
		i++;
	}
	return (count);
}

char	*remove_marks(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = -1;
	j = 0;
	while (str[++i])
		if (!((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\'))
			j++;
	ret = ft_calloc(i + 1, 1);
	i = -1;
	j = 0;
	while (str[++i])
		if (!((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\'))
			ret[j++] = str[i];
	return(free(str), ret);
}

char	*copy_arg(char *start, char *end)
{
	int		i;
	char	*ret;

	i = 0;
	while (&start[i] != end)
		i++;
	ret = ft_calloc(++i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	while (--i >= 0)
		ret[i] = start[i];
	ret = remove_marks(ret);
	return (ret);
}

char	**slice_args(char *line)
{
	int		i;
	int		y;
	t_marks	marks;
	char	**args;

	i = 0;
	y = 0;
	marks._1 = 0;
	marks._2 = 0;
	args = malloc((count_arg(line) + 1) * sizeof(char *));
	while (line[i] && line[i] != '|')
	{
		while (line[i] && line[i] == ' ')
			i++;
		args[y] = &line[i];
		while (line[i] && line[i] != ' ')
		{
			check_mark(&marks, line, i++);
			while (marks._1 != 0 || marks._2 != 0)
				check_mark(&marks, line, i++);
		}
		args[y] = copy_arg(args[y], (&line[i - 1]));
		y++;
	}
	return (args[y] = NULL, args);
}

// ----------------------------------------------------------------

// char	*arg_echo(char *line)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 4;
// 	while (line[i] == ' ')
// 		i++;
// 	tmp = str_dup_till_charset(&(line[i]), "|");
// 	return (tmp);
// }

int	parse_command(char *line, char **env)
{
	char	*arg[] = {"clear", NULL};
	// char	*tmp;
	char	**args;

	if (ft_strncmp(line, "clear", 5) == 0 && ft_strchr(" ", line[5]))
	{
		if (fork() == 0)
			execve("/usr/bin/clear", arg, env);
	}
	if (ft_strncmp(line, "exit", 4) == 0 && ft_strchr(" ", line[4]))
	{
		free(line);
		exit(0);
	}
	if (ft_strncmp(line, "echo", 4) == 0 && ft_strchr(" ", line[4]))
	{
		//fatto prima parte del aprsing per echo, penso si possa utilizzare anche per il
		// parsing generale 
		ft_printf("%s\n", line);
		args = slice_args(line);
		int i = 0;
		while (args[i] != NULL)
			ft_printf("%s\n", args[i++]);
		if (fork() == 0)
			execve("/bin/echo", args, env);
		free(args);
		// tmp = arg_echo(line);
		// if (tmp[0] == '-')
		// {
		// 	if (ft_strncmp(tmp, "-n", 2) == 0 && ft_strchr(" ", tmp[2]))
		// 		ft_printf("%s", &(tmp[2]));
		// 	else
		// 		ft_printf(RED "Error: " YELLOW "invalid option" END "\n");
		// }
		// else
		// 	ft_printf("%s\n", tmp);
		// free(tmp);
	}
	else
	{
		ft_printf(RED "Error: " YELLOW "command not found" END "\n");
		return (1);
	}
	return (0);
}
