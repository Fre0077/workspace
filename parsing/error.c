/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:57:28 by fre007            #+#    #+#             */
/*   Updated: 2025/03/13 08:28:49 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//printa l'errore in base ai caratteri ed il loro numero
void	support_print(char c, int witch, t_data *data)
{
	if (witch == 1)
	{
		printf("minishell: syntax error"
			" near unexpected token `%c'\n", c);
		data->status = 2;
	}
	else
	{
		printf("minishell: syntax error"
			" near unexpected token `%c%c'\n", c, c);
		data->status = 2;
	}
}

//trova la parte sbagliata in seguito al carattere passatogli
void	find_after_error(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] && ft_strchr("<>| ", line[i]) != NULL && !data->status)
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i + 1] == line[i])
				support_print(line[i], 2, data);
			else
				support_print(line[i], 1, data);
		}
		else if (line[i] == '|')
			support_print(line[i], 1, data);
		i++;
	}
}

//in base all'errore trovato con < & > printa
void	print_minmag_error(char *line, int *i, char c, t_data *data)
{
	int	l;

	if (line[*i + 1] == c)
		*i += 1;
	l = *i + 1;
	while (line[l] == ' ' || (line[l] == c && l == *i + 1))
		l++;
	if (!line[l])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		data->status = 2;
	}
	else
		find_after_error(&line[*i + 1], data);
}

//in base all'errore trovato con | printa
void	print_pipe_error(char *line, int i, t_data *data)
{
	int	j;
	int	l;

	j = i;
	while (j > 0 && (line[j] == ' ' || line[j] == '|'))
		j--;
	l = i + 1;
	while (line[l] && line[l] == ' ')
		l++;
	if (j == -1)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		data->status = 2;
	}
	else if (!line[l])
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		data->status = 2;
	}
	else
		find_after_error(&line[i + 1], data);
}

//controllo per eventuali errori di sintassi
int	check_syntax_error(char *line, t_data *data)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (quote_checker(line, i))
			continue ;
		if (line[i] == '|')
			print_pipe_error(line, i, data);
		else if (line[i] == '<')
			print_minmag_error(line, &i, '<', data);
		else if (line[i] == '>')
			print_minmag_error(line, &i, '>', data);
		if (data->status == 2)
			return (1);
	}
	return (0);
}
