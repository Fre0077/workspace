/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:57:05 by alborghi          #+#    #+#             */
/*   Updated: 2025/02/20 16:11:53 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

/*
struct sigaction	sa_func;

sa_func.sa_sigaction = new_prompt_sigact;
sigemptyset(&sa_func.sa_mask);
sa_func.sa_flags = 0;
*/
void	init_signals(void)
{
	signal(SIGC, new_prompt);
	// sigaction(SIGC, &sa_func, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/* void	new_prompt_sigact(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)context;
	// rl_replace_line("\n" CYAN BOLD "minishell" RED BOLD " > " END, 0);
	// ft_printf("\n" CYAN BOLD "minishell" RED BOLD " > " END);
	kill(info->si_pid, SIGKILL);
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 1;
} */

void	new_prompt(int signum)
{
	(void)signum;
	ft_printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal = 1;
}

void	get_history(int signum)
{
	HIST_ENTRY	*entry;

	ft_printf("cane");
	if (signum == ARR_UP)
	{
		ft_printf("freccia_su");
		entry = previous_history();
		if (entry != NULL)
			ft_printf("%s\n", entry->line);
	}
	else if (signum == ARR_DOWN)
	{
		ft_printf("freccia_giù");
		entry = next_history();
		if (entry != NULL)
			ft_printf("%s\n", entry->line);
	}
}
