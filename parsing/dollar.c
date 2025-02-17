/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:06:16 by fre007            #+#    #+#             */
/*   Updated: 2025/02/17 17:17:52 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//funzione che serve a copiare una stringa data all'interno di un'altra stringa (funzia)
//FORSE CI SONO TROPPE VARIBILI CONTROLLARE!!!
char	*copy_in_str(char *word, int *i, int j)
{
	char	*new_word;
	char	*env;
	char	*str;
	int		l;
	int		y;
	
	str = dup_till_n(&word[j + 1],  *i - j - 1),
	env = getenv(str);
	if (env == NULL)
		env = ft_calloc(1, 1);
	new_word = ft_calloc(1, ft_strlen(env) + ft_strlen(&word[*i]) + j + 1);
	l = -1;
	while (word[++l] != '$')
		new_word[l] = word[l];
	j = -1;
	while (env[++j])
		new_word[l++] = env[j];
	y = *i;
	*i = l;
	while (word[y])
		new_word[l++] =word[y++];
	return (free (word), free (str), new_word);
}

//serve a sostituire le variabili d'ambiente precedute dal dollaro (funziona)
char	*old_dollar_manager(char *word)
{
	int	i;
	int	j;

	i = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			while (quote_checker(word, i))
				i++;
		}
		if (word[i] == '$' && word[i + 1] != ' ' && word[i + 1])
		{
			j = i;
			i++;
			while (isalpha(word[i]))
				i++;
			word = copy_in_str(word, &i, j);
		}
		else
			i++;
	}
	return (word);
}

//rimuove i $ prima dei ' e "
char	*dollar_remover(char *word)
{
	int	i;

	i = -1;
	while (word[++i + 1])
	{
		if (word[i] == '$' && ft_strchr("\'\"", word[i + 1]))
		{
			word = remove_char(word, i);
			i--;
		}
	}
	return (word);
}

//sostituisce la variabile che gli vinee indicata tramite l'indice
char	*dollar_converter(char *word, int *i)
{
	int	j;

	j = *i;
	if (*i > 0)
		if (word[*i - 1] == '\\')
			return(remove_char(word, *i - 1));
	if (word[*i + 1] != ' ' && word[*i + 1])
	{
		*i += 1;
		while (isalpha(word[*i]))
			*i += 1;
		word = copy_in_str(word, i, j);
	}
	else
		*i += 1;
	return (word);
}

//funzione per la gestione completa del dollaro
char	*dollar_manager(char *word)
{
	int	i;

	word = dollar_remover(word);
	ft_printf("##%s\n", word);
	i = 0;
	while (word[i])
	{
		if (quote_checker(word, i) == 1)
		{
			word = remove_char(word, i);
			while (quote_checker(word, i) == 1)
				i++;
			word = remove_char(word, i);
		}
		if (word[i] == '$' && (i == 0 || word[i - 1] != '\\'))
			word = dollar_converter(word, &i);
		else
			i++;
	}
	return (word);
}
