/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_chart2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:41:06 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:41:08 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_read(t_comm *comm, t_redir *redir)
{
	if (comm->fd_read > 2)
		close(comm->fd_read);
	comm->fd_read = open_read(redir->filename);
}

void	exe_stop(t_comm *comm, t_redir *redir)
{
	if (comm->fd_read > 2)
		close(comm->fd_read);
	comm->fd_read = dub_rev_redir(redir->filename);
}

void	exe_write(t_comm *comm, t_redir *redir)
{
	if (comm->fd_write > 2)
		close(comm->fd_write);
	comm->fd_write = open_stop(redir->filename);
}

void	exe_add(t_comm *comm, t_redir *redir)
{
	if (comm->fd_write > 2)
		close(comm->fd_write);
	comm->fd_write = open_add(redir->filename);
}

int	exec_fd(t_comm *comm)
{
	t_redir	*redir;
	t_list	*strt_lst_redir;

	strt_lst_redir = comm->lst_redir;
	while (comm->lst_redir)
	{
		redir = comm->lst_redir->content;
		if (redir->type_redir == 3)
			exe_read(comm, redir);
		else if (redir->type_redir == 4)
			exe_stop(comm, redir);
		else if (redir->type_redir == 2)
			exe_add(comm, redir);
		else if (redir->type_redir == 1)
			exe_write(comm, redir);
		if (comm->fd_read == -1 || comm->fd_write == -1)
		{
			ft_lstclear(&strt_lst_redir, ft_free_redir_str);
			return (1);
		}
		comm->lst_redir = comm->lst_redir->next;
	}
	ft_lstclear(&strt_lst_redir, ft_free_redir_str);
	return (0);
}
