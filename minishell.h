/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:07:37 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/24 11:19:41 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "my_libft/my_include.h"
# include "colours.h"

# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

# include <stdio.h>

# define ARR_UP 65364
# define ARR_DOWN 65362
# define ARR_LEFT 65361
# define ARR_RIGHT 65363
# define SIGC SIGINT

extern int	g_signal;

typedef struct s_marks
{
	int	mark_1;
	int	mark_2;
}		t_marks;

// signal.c
void	init_signals(void);
void	new_prompt(int signum, siginfo_t *info, void *context);
void	get_history(int signum);

// ft_readline.c
char	*ft_strjoin_readline(char *s1, char *s2);
char	*ft_readline(char *prompt);

// parsing.c
int		parse_command(char *line, char **env);

#endif