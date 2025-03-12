/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:07:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/11 18:34:01 by alborghi         ###   ########.fr       */
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
# include <sys/stat.h>

# define HISTORY "/nfs/homes/alborghi/miei_file/42_core/milestone_3/minishell/.history"

# define ARR_UP 65364
# define ARR_DOWN 65362
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define SIGC SIGINT

# define TRUE 1
# define FALSE 0
# define CUSTOM 2

# define MINI "\001\033[1;36m\002minishell\001\033[1;31m\002 > \001\033[0m\002"

extern int			g_signal;

typedef struct s_words
{
	char			*word;
	int				pipe;
	struct s_words	*next;
}					t_words;

typedef struct s_cmd
{
	char			*divider;//prossimo elemnt di divisione tra comandi
	char			*cmd;
	char			**args;
	char			**file_i; // input
	char			**delimiter; // read till delimiter (here_doc)
	char			*file_o; // trunck (out)
	char			*file_a; // append (out)
	int				doi; //controll last readed input file (0 1 2)
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_env
{
	char			*var;
	int				is_env;
	struct s_env	*next;
}					t_env;

typedef struct s_int_list
{
	int				n;
	struct s_int_list	*next;
}					t_int_list;

typedef struct s_data
{
	t_env			*env;
	t_cmd			*cmds;
	t_cmd			*head;
	char			*find;
	char			*home;
	char			*pwd;
	t_int_list		*fds;
	int				status;
	int				stdo;
	int				stdi;
	int				prompt;
	int				out;
}					t_data;


// main.c

// init.c
t_env				*init_env(char **env);
int					init_data(t_data *data, char **env);

// signal.c
void				init_signals(void);
void				new_prompt(int signum);
void				sig_quit(int signum);
void				sig_ignore(int signum);
void				sig_here(int signum);

// ft_readline.c
char				*ft_strjoin_readline(char *s1, char *s2);
char				*ft_readline(char *prompt);

// exec.c
int					handle_files(t_cmd *cmd, t_data *data);
int					reset_std(t_data *data);
int					ft_put_env(t_env *env, int is_env);
void				ft_put_char_mat(char **mat);
void				exec_cmd(t_data *data);

// heredoc.c
void				handle_delimiter(char **delimiter, int doi, t_data *data);

// echo.c
int					exec_echo(char **args);

// cd.c
int					check_key(char *var, char *key);
char				*get_env(t_env *env, char *key);
int					set_env(t_env *env, char *key, char *value);
int					exec_cd(t_data *data);

// export.c
int					substitute_env_var(char **var, char *arg);
int					append_env_var(t_env *last, char *arg, int is_env);
int					check_arg(char *arg, char *cmd);
int					exec_export(t_cmd *cmds, t_env *env);

// unset.c
int					exec_unset(t_data *data);

// execve.c
char				*find_path(char *cmd, char *path);
int					exec_execve(t_data *data);

// ft_exit.c
void				ft_exit_builtin(t_data *data);

// int_list.c
t_int_list			*new_int_list(int n);
t_int_list			*add_int_list(t_int_list *list, int n);
void				free_int_list(t_int_list *list);
void				close_fds(t_int_list *fds);

//char_manager.c 4

int					quote_checker(char *line, int i);
char				*dup_till_n(char *start, int n, t_data *data);
char				*remove_char(char *word, int i, t_data *data);
void				set_cmd(t_cmd *cmds, t_words **words);
//------------------------------------------------------------
//dollar_stupid.c 4

char				*status_report(char *word, int *i, t_data *data);
char				*copy_in_str_stupid(char *word, int *i, int j,
						t_data *data);
char				*dollar_converter_stupid(char *word, int *i, t_data *data);
char				*dollar_manager_stupid(char *word, t_data *data);
//------------------------------------------------------------
//dollar.c 5

char				*copy_in_str(char *word, int *i, int j, t_data *data);
t_words				*multi_args_case(t_data *data, t_words *words, int *j);
t_words				*dollar_converter(char *word, int *i, t_data *data,
						t_words *words);
char				*dollar_remover(char *word, int *i, int check, t_data *data);
t_words				*dollar_manager(t_data *data, t_words *words);
//------------------------------------------------------------
//error.c 4

void				support_print(char c, int witch, t_data *data);
void				find_after_error(char *line, t_data *data);
void				print_minmag_error(char *line, int *i, char c, t_data *data);
void				print_pipe_error(char *line, int i, t_data *data);
int					check_syntax_error(char *line, t_data *data);
//------------------------------------------------------------
//exit.c 5

void				free_words_word(t_words *words);
void				free_words(t_words *words);
void				free_cmds(t_cmd *cmds);
void				free_env(t_env *env);
void				ft_exit(t_data *data, int sig);
//------------------------------------------------------------
//extra_free.c 1

void				free_words_only_pointers(t_words *words);
//------------------------------------------------------------
//inout_remover.c 4

char				*clear_2_node(t_words **tmp, t_words **first, t_data *data);
char				*clear_next_node(t_words **tmp, char *finded,
						t_words **first,	t_data *data);
char				*clear_this_node(t_words **tmp, char *finded,
						t_words **first, t_data *data);
char				*remove_last_part(t_words **tmp, char *finded,
						char *find, t_data *data);
//------------------------------------------------------------
//inout_support.c 3

char				*ft_strstr(char *big, char *little);
t_words				*remove_node_words(t_words *words, t_words *first);
char				*remove_finded(char *word, char *finded, t_data *data);
//------------------------------------------------------------
//inout.c 5

char				*find_after_word(char *find, t_words **tmp, t_data *data);
char				*findable_file(t_words *words);
void				open_useless_file(t_cmd *cmds, int witch);
void				check_file(char *find, t_words **words, t_cmd *cmds,
						t_data *data);
t_words				*inout_manager(t_words *words, t_data *data, t_cmd *cmds);
//------------------------------------------------------------
//parsing.c 5

int					count_args(t_words **words);
t_cmd				*calloc_cmds(t_data *data);
void				command_slicer(t_cmd *cmds, t_words **words,
						t_data *data, t_words **h);
t_cmd				*new_command(t_cmd *cmds, t_words **words, t_data *data);
t_cmd				*parsing(char *line, t_data *data);
//------------------------------------------------------------
//print.c 3

void				print_word(t_words *words);
void				print_i_delimiter(t_cmd *cmds);
void				print_cmd(t_cmd *cmds);
void				print_data(t_data *data);
//------------------------------------------------------------
//word.c 4

t_words				*pipe_manager(int *i, t_data *data, t_words *words);
char				*next_word(char *line, int *i, t_data *data);
t_words				*new_word(t_words *words, char *str, t_data *data);
t_words				*word_slicer(char *line, t_data *data);
//------------------------------------------------------------
#endif