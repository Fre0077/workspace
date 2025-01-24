/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:25:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/24 19:24:33 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_mark(t_marks *marks, char *c, int i)
{
	if (c[i] == '\'' && c[i - 1] != '\\' && marks->mark_1 == 0
		&& marks->mark_2 == 0)
		return (marks->mark_1 = 1, 1);
	else if (c[i] == '"' && c[i - 1] != '\\' && marks->mark_1 == 0
		&& marks->mark_2 == 0)
		return (marks->mark_2 = 1, 1);
	else if (c[i] == '\'' && c[i - 1] != '\\' && marks->mark_1 == 1)
		return (marks->mark_1 = 0, 0);	
	else if (c[i] == '"' && c[i - 1] != '\\' && marks->mark_2 == 1)
		return (marks->mark_2 = 0, 0);
	return (0);
}

int	count_arg(char *line)
{
	int		count;
	int		i;
	t_marks	marks;

	i = 0;
	count = 0;
	marks.mark_1 = 0;
	marks.mark_2 = 0;
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ' && marks.mark_1 == 0 && marks.mark_2 == 0)
			i++;
		if (check_mark(&marks, line, i))
			count++;
		else if (((line[i - 1] == ' ' && line[i])
			|| (line[i - 1] != ' ' && i == 0))
			&& marks.mark_1 == 0 && marks.mark_2 == 0)
			count++;
		i++;
	}
	return (count);
}

char	*copy_arg(t_marks marks, char *line) //ultimo pezzo per dividere per bene, deve prendere i caratteri dopo i ' 
{
	if (marks.mark_1 == 1)
		return(str_dup_till_charset(line, "'"));
	else if (marks.mark_2 == 1)
		return(str_dup_till_charset(line, "\""));
	else
		return(str_dup_till_charset(line, " \0"));
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
	ft_printf("j:%d\n", j);
	ret = ft_calloc(i + 1, 1);
	i = -1;
	j = 0;
	while (str[++i])
		if (!((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\'))
			ret[j++] = str[i];
	ft_printf("str:%s             ret:%s\n", str, ret);
	return(free(str), ret);
}

char	**slice_args(char *line)
{
	int		i;
	int		y;
	t_marks	marks;
	char	**args;

	i = 0;
	y = 0;
	marks.mark_1 = 0;
	marks.mark_2 = 0;
	args = malloc((count_arg(line) + 1) * 8);
	while (line[i] && line[i] != '|')
	{
		while (line[i] == ' ' && marks.mark_1 == 0 && marks.mark_2 == 0)
			i++;
		if (check_mark(&marks, line, i))
		{
			args[y++] = copy_arg(marks, &(line[++i]));
		}
		else if (((line[i - 1] == ' ' && line[i]) || (line[i - 1] != ' ' && i == 0))
			&& marks.mark_1 == 0 && marks.mark_2 == 0)
		{
			args[y++] = copy_arg(marks, &(line[i]));
			i += ft_strlen(args[y - 1]);
			if (ft_strchr(args[y - 1], '\''))
				args[y - 1] = remove_marks(args[y - 1]);
			if (ft_strchr(args[y - 1], '\"'))
				args[y - 1] = remove_marks(args[y - 1]);
		}
		i++;
	}
	args[y] = NULL;
	return (args);
}

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
		ft_printf("%s\n", line);
		args = slice_args(line);
		int i = 0;
		while (args[i] != NULL)
			ft_printf("%s\n", args[i++]);
		// char *args[] = {
		// "echo",
		// "1$",
		// "$",
		// "$\"c\"",
		// "c",
		// "\"$\"c",
		// "\"",
		// "\"c",
		// "$ac",
		// "\"",
		// "$a",
		// "\"c",
		// NULL
		// };
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
