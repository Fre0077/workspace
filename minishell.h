/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:07:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/29 11:51:28 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "colours.h"
# include "my_libft/my_include.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

# define ARR_UP 65364
# define ARR_DOWN 65362
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define SIGC SIGINT

extern int			g_signal;

typedef struct s_marks //cambiare nomi in q (qhote) e dq (double quote)
{
	int				_1;
	int				_2;
}					t_marks;

typedef struct s_words
{
	char			*word;
	struct s_words	*next;
}					t_words;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}					t_cmd;

// signal.c
void				init_signals(void);
void				new_prompt(int signum, siginfo_t *info, void *context);
void				get_history(int signum);

// ft_readline.c
char				*ft_strjoin_readline(char *s1, char *s2);
char				*ft_readline(char *prompt);

// parsing.c
int					parse_command(char *line, char **env);

// parse_words.c
int					check_mark(t_marks *marks, char *c, int i);
int					count_arg(char *line);
char				*copy_arg(char *start, char *end);
char				**slice_args(char *line);
t_words				*parse_words(char *line);

#endif