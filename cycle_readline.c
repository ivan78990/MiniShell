/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_readline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:40:12 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:40:13 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	conrol_d(void)
{
	write(2, "\e[1A\e[11Cexit\n", 15);
	exit(0);
}

void	ft_conveer(t_list *lst_comm, t_data *data)
{
	if (lst_comm)
	{
		signals_new();
		if (lst_comm->next)
		{
			if (exec_fork(lst_comm, data, STDIN_FILENO) != -1)
				wait_child_process(lst_comm);
			else
				kill_child_process(lst_comm);
		}
		else
			simplest_exec(lst_comm->content, data);
		ft_free_lst_comm(lst_comm);
	}
}

void	cycle_readline(t_list *lst_comm, t_data *data, char *input)
{
	rl_outstream = stderr;
	while (!data->flag_end)
	{
		input = readline("minishell: ");
		if (input == NULL)
			break ;
		lst_comm = ft_preparser(data, input);
		add_history(input);
		ft_conveer(lst_comm, data);
		signal_normal();
		ft_refresh_dollar_quest(data);
		free(input);
	}
}
