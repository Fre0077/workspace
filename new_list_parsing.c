/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/02/12 20:28:20 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//printa tutta al  lista dei comandi (funzionante)
void	print_word(t_words *words)
{
	while (words->next != NULL)
	{
		ft_printf("%s\n", words->word);
		words = words->next;
	}
}

//printa tutta la lista dei comandi (funzia)
void	print_cmd(t_cmd *cmds)
{
	int	i = 0;

	while (cmds != NULL)
	{
		ft_printf("cmd: %s\n", cmds->cmd);
		i = -1;
		ft_printf("arg: ");
		while (cmds->args[++i] != NULL)
			ft_printf("%s, ", cmds->args[i]);
		ft_printf("\n");
		cmds = cmds->next;
	}
}

//duplica per n cartterei (funzionante)
char	*dup_till_n(char *start, int n)
{
	char	*str;

	str = ft_calloc(1, n + 1);
	while (--n >= 0)
		str[n] = start[n];
	return (str);
}

//funzione che tiene controllato se si è all'interno di virgolette (funzionante)
int	quote_checker(char *line, int i)
{
	static int	mark;

	if (!line[i])
		return (mark = 0, 0);
	if (line[i] == '\'')
	{
		if (i == 0 || (line[i - 1] != '\\' && mark == 0))
			mark = 1;
		else if (line[i - 1] != '\\' && mark == 1)
			mark = 0;
	}
	if (line[i] == '\"')
	{
		if (i == 0 || (line[i - 1] != '\\' && mark == 0))
			mark = 2;
		else if (line[i - 1] != '\\' && mark == 2)
			mark = 0;
	}
	if (mark != 0)
		return (1);
	return (0);
}

//data la stringa rimuove il carattere ocrrispondente al numero dato (funzia)
char	*remove_char(char *word, int i)
{
	char	*new_word;
	int		j;
	int		l;

	new_word = ft_calloc(1, ft_strlen(word));
	j = -1;
	l = -1;
	while (word[++j])
	{
		if (i == j)
		j++;
		new_word[++l] = word[j];
	}
	return (free(word), new_word);
}

//elimina le quote identificate da quote_checker
char	*quote_remover(char *word)
{
	int	i;
	int	check;
	int	pre;

	i = -1;
	check = 0;
	while (word[++i])
	{
		pre = check;
		check = quote_checker(word, i);
		if (pre != check)
		{
			word = remove_char(word, i);
			i--;
		}
	}
	return (word);
}

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
	return (word);
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

char	*dollar_manager(char *word)
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
		if (word[i] == '$')
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

//crea nuovo nodo della lista e scorre ad esso dopo aver impostato la parola appena trovata (funzionante)
t_words	*new_word(char *word, t_words *words)
{
	word = dollar_manager(word); //usare getenv
	words->word = quote_remover(word);
	words->next = malloc(sizeof(t_words));
	words = words->next;
	return (words);
}

char	*pipe_manager(int *i)
{
	char	*str;

	str = ft_calloc(1, 2);
	str[0] = '|';
	i += 1;
	return (str);
}

//divide la linea in parti considerando le quote (funzionante)
//non piglia le virgolette se sono all'inizio (risolto)
//l'ultimo elemento non è nul ma un nodo vuoto, sarebbe meglio fixare questa cosa
t_words	*word_slicer(char *line)
{
	int		i;
	int		start;
	t_words	*first;
	t_words	*words;

	i = -1;
	words = malloc(sizeof(t_words));
	first = words;
	while (line[++i])
	{
		if (line[i] != ' ' && line[i] != '|')
		{
			start = i;
			while ((quote_checker(line, i) || (line[i] != ' ' && line[i] != '|')) && line[i])
				i++;
			words = new_word(dup_till_n(&line[start], i - start), words);
		}
		if (line[i] == '|')
			words = new_word(pipe_manager(&i), words);
	}
	words->next = NULL;
	return (first);
}

//funzione per la scrittura dei comandi nella lista e per la creazione dei nuovi nodi (funzia)
void	command_slicer(t_cmd *cmds, t_words **words)
{
	t_words	*arg;
	int		i;
	int		j;

	cmds->cmd = (*words)->word;
	arg = (*words)->next;
	(*words) = (*words)->next;
	i = 0;
	while ((*words)->next != NULL) //possibile aggiunta dell '&&'
	{
		if ((*words)->word[0] == '|')
			return ;
		(*words) = (*words)->next;
		i++;
	}
	cmds->args = malloc(sizeof(char *) * (i + 1));
	cmds->args[i] = NULL;
	j = -1;
	while (--i >= 0)
	{
		cmds->args[++j] = arg->word;
		arg = arg->next;
	}
}

//funzione lanciata per creare un nodo della lista cmds, setta anche gli argomenti
t_cmd	*new_command(t_cmd *cmds, t_words **words)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd));
	cmds->next = new_cmd;
	command_slicer(new_cmd, words);
	return (new_cmd);
}

//funzione principale per la gestione di tutto il parsing (da testare)
t_cmd	*parsing(char *line)
{
	t_words	*words;
	t_cmd	*cmds;
	t_cmd	*first;

	if (line[0] == '\0')
		return (NULL);
	words = word_slicer(line);
	ft_printf("--------\n");
	print_word(words);
	ft_printf("--------\n");
	cmds = malloc(sizeof(t_cmd));
	command_slicer(cmds, &words);
	first = cmds;
	while (words->next != NULL)
		cmds = new_command(cmds, &words);
	cmds->next = NULL;
	print_cmd(first);
	ft_printf("--------\n");
	return (first);
}
