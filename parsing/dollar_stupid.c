/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_stupid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:16 by fre007            #+#    #+#             */
/*   Updated: 2025/03/11 13:44:16 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//sostituisce il $? con il valore di status attuale
char	*status_report(char *word, int *i, t_data *data)
{
	char	*new_word;
	char	*str;
	int		l;
	int		y;

	str = ft_itoa(data->out);
	new_word = ft_calloc(1, ft_strlen(str) + ft_strlen(word) - 1);
	if (!new_word)
		ft_exit(data, 1);
	l = -1;
	while (++l != *i)
		new_word[l] = word[l];
	y = -1;
	while (str[++y])
		new_word[l++] = str[y];
	y = *i + 2;
	*i = l;
	while (word[y])
		new_word[l++] = word[y++];
	return (free (word), free (str), new_word);
}

//sostituisce la variabile indicata con il valore dell'env corrispondente
char	*copy_in_str_stupid(char *word, int *i, int j, t_data *data)
{
	char	*new_word;
	char	*env;
	char	*str;
	int		l;
	int		y;

	str = dup_till_n(&word[j + 1], *i - j - 1, data);
	env = get_env(data->env, str);
	new_word = ft_calloc(1, ft_strlen(env) + ft_strlen(&word[*i]) + j + 1);
	if (!new_word)
		ft_exit(data, 1);
	l = -1;
	while (++l != j)
		new_word[l] = word[l];
	j = -1;
	while (env != NULL && env[++j])
		new_word[l++] = env[j];
	y = *i;
	*i = l;
	while (word[y])
		new_word[l++] = word[y++];
	return (free (word), free (str), new_word);
}

//sostituisce la variabile che gli viene indicata tramite l'indice
char	*dollar_converter_stupid(char *word, int *i, t_data *data)
{
	int	j;

	j = *i;
	if (*i > 0 && word[*i - 1] == '\\')
		return (remove_char(word, *i - 1, data));
	if (word[*i + 1] == '?')
		word = status_report (word, i, data);
	else if (ft_isalnum(word[*i + 1]) || word[*i + 1] == '_')
	{
		*i += 1;
		if (!ft_isdigit(word[*i]))
		{
			while (ft_isalnum(word[*i]) || word[*i] == '_')
				*i += 1;
		}
		word = copy_in_str(word, i, j, data);
	}
	else
		*i += 1;
	return (word);
}

//gestione il simbolo $ e le quote
char	*dollar_manager_stupid(char *word, t_data *data)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && (i == 0 || word[i - 1] != '\\'))
			word = dollar_converter_stupid(word, &i, data);
		else
			i++;
	}
	return (word);
}
