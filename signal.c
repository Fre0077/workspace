/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alborghi <alborghi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:57:05 by alborghi          #+#    #+#             */
/*   Updated: 2025/01/23 18:29:22 by alborghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal;

void	init_signals(void)
{
	signal(SIGC, new_prompt);  // Ctrl+C
	signal(SIGQUIT, SIG_IGN); // Ctrl+backslash
	signal(ARR_UP, get_history); 
	signal(ARR_DOWN, get_history); 
}

void	new_prompt(int signum)
{
	(void)signum;
	// rl_replace_line("\n" CYAN BOLD "minishell" RED BOLD " > " END, 0);
	rl_replace_line("", 0);
	// ft_printf("\n" CYAN BOLD "minishell" RED BOLD " > " END);
	ft_printf("\n");
	rl_on_new_line();
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