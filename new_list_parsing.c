/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/02/02 16:25:48 by fre007           ###   ########.fr       */
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

//funzione che tiene controllato se si è all'interno di virgolette (funzionante)
//ATTENZIONE: possibili problemi con quote non chiuse (e invece funziona)
int	quote_checker(char *line, int *i)
{
	static int	mark;

	if (!line[*i])
		return (mark = 0, 0);
	if (line[*i] == '\'')
	{
		if (*i != 0 && line[*i - 1] != '\\' && mark == 0)
			mark = 1;
		else if (*i != 0 && line[*i - 1] != '\\' && mark == 1)
			mark = 0;
	}
	if (line[*i] == '\"')
	{
		if (*i != 0 && line[*i - 1] != '\\' && mark == 0)
			mark = 2;
		else if (*i != 0 && line[*i - 1] != '\\' && mark == 2)
			mark = 0;
	}
	if (mark != 0)
		return (1);
	return (0);
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

//rimuove solo le quote più esterne dalle varie parole
//FUNZIONA MA TROPPO LUNGA, METTENDO SOLO L'ALLOCAZIONE MAGGIORE UFNZIONA MA NON MI PIACE
char	*quote_remover(char *word)
{
	int		i;
	int		j;
	int		y;
	int		t;
	char	*new_word;

	i = -1;
	while (word[++i])
		if (word[i] == '\"' || word[i] == '\'')
			break;
	j = -1;
	while (word[++j])
		if ((word[j] == '\"' || word[j] == '\'') && j != i && word[i] == word[j])
			break;
	ft_printf("i:%d   j:%d\n", i, j);
	if (!word[i])
		return (word);
	else if (!word[j])
		new_word = ft_calloc(1, ft_strlen(word));
	else
		new_word = ft_calloc(1, ft_strlen(word) - 1);
	y = -1;
	t = -1;
	while (word[++y])
		if (y != i && y != j)
			new_word[++t] = word[y];
	return (new_word);
}

//crea nuovo nodo della lista e scorre ad esso dopo aver impostato la parola appena trovata (funzionante)
t_words	*new_word(char *word, t_words *words)
{
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
//no piglia le virgolette se sono all'inizio
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
			while ((quote_checker(line, &i) || (line[i] != ' ' && line[i] != '|')) && line[i])
				i++;
			words = new_word(dup_till_n(&line[start], i - start), words);
		}
		if (line[i] == '|')
			words = new_word(pipe_manager(&i), words);
	}
	words->next = NULL;
	return (first);
}

//printa tutta al  lista dei comandi (da testare)
void	print_cmd(t_cmd *cmd)
{
	(void)cmd;
}

//funzione per la scrittura dei comandi nella lista e per la creazione dei nuovi nodi
void	new_command(t_cmd *cmds, t_words **words)
{
	(void)cmds;
	(void)words;
}

//funzione per controllare che il comando e gli argomenti dati siano corretti
int	error_checker(t_cmd *cmd)
{
	(void)cmd;
	return 0;
}

//funzione principale per la gestione di tutto il parsing (da testare)
t_cmd	*parsing(char *line)
{
	//int		i;
	t_words	*words;
	//t_cmd	*cmds;
	//t_cmd	*first;

	words = word_slicer(line);
	ft_printf("--------\n");
	print_word(words);
	ft_printf("--------\n");
	//i = 0;
	//cmds = malloc(sizeof(t_cmd));
	//first = cmds;
	//while (words != NULL)
	//{
	//	new_command(cmds, &words);
	//	if (error_checker(cmds))
	//		break ;
	//	cmds = cmds->next;
	//}
	//ft_printf("--------\n");
	//return (first);
	return (NULL);
}
