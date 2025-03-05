/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:07:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/05 14:51:32 by alborghi         ###   ########.fr       */
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

# define HISTORY "/nfs/homes/alborghi/miei_file/42_core/milestone_3/minishell/.history"

# define ARR_UP 65364
# define ARR_DOWN 65362
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define SIGC SIGINT

# define TRUE 1
# define FALSE 0
# define CUSTOM 2

# define MINI "\001"CYAN BOLD"\002minishell\001"RED BOLD"\002 > \001"END"\002"

extern int			g_signal;

typedef struct s_words
{
	char			*word;
	struct s_words	*next;
}					t_words;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*file_o; // trunck (out)
	char			*file_a; // append (out)
	int				doi; //controll last readed input file (0 1 2)
	char			**file_i; // input
	char			**delimiter; // read till delimiter (here_doc)
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
	t_cmd			*head;
	int				status;
	int				stdo;
	int				stdi;
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

//--------------------------------------------------------

//parsing.c

void				command_slicer(t_cmd *cmds, t_words **words, t_data *data, t_words **h);
t_cmd				*new_command(t_cmd *cmds, t_words **words, t_data *data);
t_cmd				*parsing(char *line, t_data *data);

//word.c

char				*pipe_manager(int *i, t_data *data);
char				*next_word(char *line, int *i, t_data *data);
t_words				*new_word(t_words *words, char *str, t_data *data);
t_words				*word_slicer(char *line, t_data *data);

//dollar.c

char				*copy_in_str(char *word, int *i, int j, t_data *data);
char				*dollar_converter(char *word, int *i, t_data *data);
char				*dollar_remover(char *word, int *i, int check, t_data *data);
char				*dollar_manager(char *word, t_data *data);

//dollar.c

char				*copy_in_str_stupid(char *word, int *i, int j, t_data *data);
char				*dollar_converter_stupid(char *word, int *i, t_data *data);
char				*dollar_remover_stupid(char *word, int *i, int check, t_data *data);
char				*dollar_manager_stupid(char *word, t_data *data);

//char_manager.c

int					quote_checker(char *line, int i);
char				*dup_till_n(char *start, int n, t_data *data);
char				*remove_char(char *word, int i, t_data *data);

//inout.c

char				*ft_strstr(char *big, char *little);
t_words				*remove_node_words(t_words *words, t_words *first);
char				*remove_finded(char *word, char *finded, t_data *data);
char				*clear_2_node(t_words **tmp, t_words **first, t_data *data);
char				*clear_next_node(t_words **tmp, char *finded,
									t_words **first,	t_data *data);
char				*clear_this_node(t_words **tmp, char *finded,
									t_words **first, t_data *data);
char				*remove_last_part(t_words **tmp, char *finded,
									char *find, t_data *data);
int					check_sintax_error(t_words *tmp, char *finded,
									char *find, t_data *data);
char				*find_after_word(char *find, t_words **tmp, t_data *data);
t_words				*inout_manager(t_words *words, t_data *data, t_cmd *cmds);

//print.c

void				print_word(t_words *words);
void				print_cmd(t_cmd *cmds);
void				print_data(t_data *data);

//exit.c

void				free_cmds(t_cmd *cmds);
void				free_words(t_words *words);
void				ft_exit(t_data *data, int sig);

//------------------------------------------------------------

// exec.c
int					handle_files(t_cmd *cmd, t_data *data);
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
char				*find_path(char *cmd, char *path);
int					exec_execve(t_data *data);

// ft_exit.c
void				ft_exit_builtin(t_data *data);

#endif