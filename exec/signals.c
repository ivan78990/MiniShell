/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:38:52 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:38:54 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		write (2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.return_value = 130;
	}
}

void	signal_normal(void)
{
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_ign(int signo)
{
	(void)signo;
	signal(SIGINT, SIG_IGN);
}

void	signals_def(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signals_new(void)
{
	signal(SIGINT, signals_ign);
	signal(SIGQUIT, signals_ign);
}
