/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:57:28 by fre007            #+#    #+#             */
/*   Updated: 2025/03/08 15:22:18 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//controllo per eventuali errori di sintassi
int	check_syntax_error(char *line, t_data *data)
{
	int	pos;
	int	pos2;
	int	pos3;

	pos = search_for_pip(line);
	pos2 = search_for_minmag(line, '<');
	pos3 = search_for_minmag(line, '>');
	if ((pos3 != -1 && pos2 > pos3) || pos2 == -1)
		pos2 = pos3;
	if (pos != -1 || pos2 != -1)
		print_syntax_error(line, pos, pos2, data);
	return (data->status);
}

//stampa il messaggio di errore corretto
void	print_syntax_error(char *line, int pos, int pos2, t_data *data)
{
	if ((pos != -1 && !line[pos]) || (pos2 != -1 && !line[pos2]))
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
	if (support_print(line, pos, pos2, '<'))
		data->status = 1;
	else if (support_print(line, pos, pos2, '>'))
		data->status = 1;
	else if ((pos != -1 && line[pos] == '|') 
			|| (pos2 != -1 && line[pos2] == '|'))
		ft_printf("minishell: syntax error near unexpected token `|'\n");
	data->status = 1;
}

//funzione di suppoto al print dei syntax error
int	support_print(char *line, int pos, int pos2, char c)
{
	if (((pos2 < pos || pos == -1) && pos2 != -1 && line[pos2] == c)
		|| (pos != -1 && line[pos] == c))
	{
		if ((pos2 != -1 && line[pos2] && line[pos2 + 1] == c)
			|| (pos != -1 && line[pos] && line[pos + 1] == c))
		{
			ft_printf("minishell: syntax error near unexpected token `%c%c'\n"
						, c, c);
		}
		else
		{
			ft_printf("minishell: syntax error near unexpected token `%c'\n"
						, c);
		}
		return (1);
	}
	return (0);
}

// ricerca degli errori si sintassi inerenti a < & >
int	search_for_minmag(char *line, char c)
{
	int	i;
	int	find;
	int	check;

	i = -1;
	find = 0;
	while (line != NULL && line[++i])
	{
		check = quote_checker(line, i);
		if (find == 1  && c == '>' && line[i] != ' ' && line[i] != '>')
			break ;
		if (find == 1  && c == '<' && line[i] != ' ' && line[i] != '<')
			break ;
		if (find == 2 && line[i] != ' ')
			break ;
		if (!check && line[i] == c)
			find++;
	}
	quote_checker("1", 1);
	if (find == 0)
		return (-1);
	return (i);
}

// ricerca degli errori si sintassi inerenti alla |
int	search_for_pip(char *line)
{
	int	i;
	int	find;
	int	check;

	i = -1;
	find = 0;
	while (line != NULL && line[++i])
	{
		check = quote_checker(line, i);
		if (find == 1 && line[i] != ' ')
			break ;
		if (!check && line[i] == '|')
			find++;
	}
	quote_checker("1", 1);
	if (find == 0)
		return (-1);
	return (i);
}
