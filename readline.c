/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:50:28 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:50:30 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_preparser(t_data *data, char *input)
{
	t_list	*lst_comm;
	int		str_len;
	int		flag_error_syntax;
	t_list	*lst_token;

	lst_token = NULL;
	lst_comm = NULL;
	flag_error_syntax = 0;
	str_len = (int)ft_strlen(input);
	if (ft_check_syntax(input, str_len))
		return (ft_put_syntax_error("syntax error"));
	lst_token = ft_get_token(input, &flag_error_syntax);
	if (flag_error_syntax)
	{
		ft_lstclear(&lst_token, ft_free_ptr);
		return (ft_put_syntax_error("syntax error"));
	}
	data->count_pipe = ft_get_count_pipe(lst_token);
	lst_comm = ft_parser(data, lst_token);
	ft_lstclear(&lst_token, ft_free_ptr);
	return (lst_comm);
}

void	ft_prepare(t_data *data, char **env)
{
	t_lst_env	*lst_env;

	lst_env = NULL;
	rl_outstream = stderr;
	rl_bind_key('\t', rl_complete);
	if (!data->count_env)
		lst_env = ft_get_lst_ienv(data);
	else
		lst_env = ft_get_envlist_of_envarr(env, data);
	data->lst_env = lst_env;
	ft_get_new_lst_env(data, "?=0", "?", "0");
	ft_up_shlvl(lst_env, data);
	data->my_env = ft_get_envarr_of_envlst(data->lst_env, data);
	data->count_env++;
}

void	kill_child_process(t_list *lst_comm)
{
	t_comm	*comm;

	comm = NULL;
	while (lst_comm)
	{
		comm = lst_comm->content;
		if (comm->pid)
			kill(comm->pid, SIGKILL);
		lst_comm = lst_comm->next;
	}
}

void	wait_child_process(t_list *lst_comm)
{
	int		status;
	int		i;
	int		wait_pid;
	t_comm	*comm;

	comm = NULL;
	while (lst_comm)
	{
		comm = lst_comm->content;
		wait_pid = waitpid(comm->pid, &status, 0);
		g_global.return_value = WEXITSTATUS(status);
		i = (-1 == wait_pid);
		if (!i)
		{
			g_global.return_value = WEXITSTATUS(status);
			if (g_global.return_value == 130)
			{
				kill_child_process(lst_comm);
				break ;
			}
			lst_comm = lst_comm->next;
		}
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_data	*data;
	t_list	*lst_comm;
	char	*input;

	lst_comm = NULL;
	(void)argv;
	(void)argc;
	input = NULL;
	data = ft_init_data(env);
	ft_prepare(data, env);
	signal_normal();
	cycle_readline(lst_comm, data, input);
	conrol_d();
}
