/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:07:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/18 18:07:27 by alborghi         ###   ########.fr       */
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
# include <stdlib.h>
# include <sys/wait.h>

# define ARR_UP 65364
# define ARR_DOWN 65362
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define SIGC SIGINT

# define TRUE 1
# define FALSE 0
# define CUSTOM 2

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

typedef struct s_env
{
	char			*var;
	int				is_env;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env			*env;
	t_cmd			*cmds;
	int				status;
	char			*home;
	char			*pwd;
	char			*oldpwd;
}					t_data;

// main.c

// init.c
void				free_env(t_env *env);
t_env				*init_env(char **env);
int					init_data(t_data *data, char **env);

// signal.c
void				init_signals(void);
void				new_prompt_sigact(int signum, siginfo_t *info,
		void *context);
void				new_prompt(int signum);
void				get_history(int signum);

// ft_readline.c
char				*ft_strjoin_readline(char *s1, char *s2);
char				*ft_readline(char *prompt);

//parsing.c
t_cmd				*parsing(char *line);

//print.c
void	print_word(t_words *words);
void	print_cmd(t_cmd *cmds);

//quote.c
int		quote_checker(char *line, int i);
char	*quote_remover(char *word);

//dollar.c
char	*dollar_manager(char *word);

//char_manager.c
char	*dup_till_n(char *start, int n);
char	*remove_char(char *word, int *i);
char	*copy_in_str(char *word, int *i, int j);

//word.c
char	*pipe_manager(int *i);
char	*next_word(char *line, int *i);
t_words	*new_word(t_words *words, char *str);
t_words	*word_slicer(char *line);

// exec.c
void				ft_put_env(t_env *env, int is_env);
void				ft_put_char_mat(char **mat);
void				exec_cmd(t_data *data);

// echo.c
void				exec_echo(char **args);

// cd.c
int					check_key(char *var, char *key);
char				*get_env(t_env *env, char *key);
int					set_env(t_env *env, char *key, char *value);
int					exec_cd(t_data *data);

// export.c
int					exec_export(t_cmd *cmds, t_env *env);

// unset.c
int					exec_unset(t_data *data);

// execve.c
int					exec_execve(t_data *data);

#endif