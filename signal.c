/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:57:05 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/11 11:07:33 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	init_signals(void)
{
	signal(SIGC, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	new_prompt(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 1;
}

void	sig_quit(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	exit(131);
}

void	sig_ignore(int signum)
{
	printf("\001");
	(void)signum;
	printf("\002");
}

void	sig_here(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		close(0);	
	}
}