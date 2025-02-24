/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:16 by fre007            #+#    #+#             */
/*   Updated: 2025/02/24 13:14:42 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//sostituisce la variabile indicata con il valore dell'env corrispondente
char	*copy_in_str(char *word, int *i, int j, t_data *data)
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
		ft_exit(data);
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
char	*dollar_converter(char *word, int *i, t_data *data)
{
	int	j;

	j = *i;
	if (*i > 0 && word[*i - 1] == '\\')
		return (remove_char(word, *i - 1, data));
	if (ft_isalpha(word[*i + 1]))
	{
		*i += 1;
		while (ft_isalpha(word[*i]))
			*i += 1;
		word = copy_in_str(word, i, j, data);
	}
	else
		*i += 1;
	return (word);
}

//rimuove i $ prima dei ' e "
char	*dollar_remover(char *word, int *i, int check, t_data *data)
{
	if (word[*i] == '$' && (word[*i + 1] == '\'' || word[*i + 1] == '\"')
		&& (*i == 0 || word[*i - 1] != '\\') && check == 0)
		word = remove_char(word, *i, data);
	return (word);
}

//gestione il simbolo $ e le quote
char	*dollar_manager(char *word, t_data *data)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (word[i])
	{
		word = dollar_remover(word, &i, check, data);
		check = quote_checker(word, i);
		if (check != 1 && word[i] == '$' && (i == 0 || word[i - 1] != '\\'))
			word = dollar_converter(word, &i, data);
		//else if (((check != 1 && word[i] == '$') || word[i] == '\''
		//		|| word[i] == '\"') && i != 0 && word[i - 1] == '\\')
		//	word = remove_char(word, i - 1, data);
		else
			i++;
	}
	return (word);
}
