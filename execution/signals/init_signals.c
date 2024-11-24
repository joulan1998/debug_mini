/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 16:43:28 by ael-garr          #+#    #+#             */
/*   Updated: 2024/11/03 15:29:27 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c_sig(int sig)
{
	if (g_signal == 1)
		return ;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

static void	sig_quit_handler(int sig)
{
	if (g_signal == 1)
		return ;
	(void)sig;
}

void	init_signl(int catch_signal)
{
	if (catch_signal)
		rl_catch_signals = 0;
	signal(SIGINT, ctrl_c_sig);
	signal(SIGQUIT, sig_quit_handler);
}
