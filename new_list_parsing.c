/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_list_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 09:57:09 by fre007            #+#    #+#             */
/*   Updated: 2025/02/13 14:54:12 by alborghi         ###   ########.fr       */
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
int	quote_checker(char *line, int *i)
{
	static int	mark;

	if (!line[*i])
		return (mark = 0, 0);
	if (line[*i] == '\'')
	{
		if (*i == 0 || (line[*i - 1] != '\\' && mark == 0))
			mark = 1;
		else if (line[*i - 1] != '\\' && mark == 1)
			mark = 0;
	}
	if (line[*i] == '\"')
	{
		if (*i == 0 || (line[*i - 1] != '\\' && mark == 0))
			mark = 2;
		else if (line[*i - 1] != '\\' && mark == 2)
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

char	*copy_in_str(char *word, char *word_$, int i_$, char *env)
{
	printf("@@@@@@%s\n@@@@@@%s\n", word_$, env);
	int		i;
	int		j;
	char	*new_word;

	if (env == NULL)
		return (word);
	i = 1;
	while (isalpha(word_$[i]))
		i++;
	new_word = ft_calloc(1, ft_strlen(env) + ft_strlen(&word_$[i]) + i_$ + 2);
	i_$ = -1;
	while (word[++i_$] != '$')
		new_word[i_$] = word[i_$];
	j = -1;
	while (env[++j])
		new_word[i_$++] = env[j];
	while (word_$[i])
		new_word[i_$++] = word_$[i++];
	return (free (word), new_word);
}

char	*dollar_manager(char *word)
{
	int		i;
	int		i_$;
	int		j;
	char	*str;

	i = 0;
	while (word[i] != '$' && word[i])
		i++;
	if (!word[i])
		return (word);
	i_$ = i;
	j = 0;
	while (isalpha(word[++i]))
		j++;
	str = ft_calloc(1, j + 1);
	while (--j >= 0)
		str[j] = word[--i];
	word = copy_in_str(word, &word[i_$], i_$, getenv(str));
	ft_printf("######: %s\n", str);
	return (free (str), word);
}

//rimuove solo le quote più esterne dalle varie parole
char	*quote_remover(char *word)
{
	int		i[4];
	char	*new_word;

	i[0] = -1;
	while (word[++i[0]])
		if (quote_checker(word, &i[0]) == 1)
			break;
	i[1] = i[0];
	while (word[++i[1]])
		if (quote_checker(word, &i[1]) == 0)
			break;
	if (!word[i[0]])
		return (word);
	else if (!word[i[1]])
		new_word = ft_calloc(1, ft_strlen(word));
	else
		new_word = ft_calloc(1, ft_strlen(word) - 1);
	i[2] = -1;
	i[3] = -1;
	while (word[++i[2]])
		if (i[2] != i[0] && i[2] != i[1])
			new_word[++i[3]] = word[i[2]];
	return (new_word);
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

//printa tutta al  lista dei comandi (funzia)
void	print_cmd(t_cmd *cmds)
{
	int	i = 0;

	while (cmds != NULL)
	{
		ft_printf("cmd: %s\n", cmds->cmd);
		i = -1;
		ft_printf("arg: ");
		if (cmds->args == NULL)
		{
			cmds = cmds->next;
			ft_printf("\n");
			continue ;
		}
		while (cmds->args[++i] != NULL)
			ft_printf("%s, ", cmds->args[i]);
		ft_printf("\n");
		cmds = cmds->next;
	}
}

//funzione per controllare che il comando e gli argomenti dati siano corretti
//includere il finding
int	error_checker(t_cmd *cmd)
{
	(void)cmd;
	return 0;
}

//funzione per la scrittura dei comandi nella lista e per la creazione dei nuovi nodi (funzia)
void	command_slicer(t_cmd *cmds, t_words **words)
{
	t_words	*arg;
	int		i;
	int		j;

	error_checker(cmds);
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
