/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:18:07 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:18:09 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_prepare_get_command(t_comm **new_command, t_list **lst_redir,
							   t_count *cnt, t_list **lst_arg)
{
	cnt->count_drop_token += cnt->count_drop_token_redir;
	*new_command = NULL;
	*lst_redir = NULL;
	*lst_arg = NULL;
	cnt->count_drop_token_redir = 0;
	*new_command = ft_init_command_struct();
}

t_comm	*ft_parse_token_for_comm(t_count *cnt, t_list *lst_tkn, t_data *data)
{
	t_list	*lst_redir;
	t_list	*lst_arg;
	t_comm	*new_command;

	ft_prepare_get_command(&new_command, &lst_redir, cnt, &lst_arg);
	while ((cnt->flag == 1 || cnt->flag == 3) && lst_tkn)
	{
		cnt->flag = ft_flag_token(lst_tkn, data);
		if (cnt->flag == 1)
		{
			ft_lstadd_back(&lst_arg, ft_lstnew(ft_strdup(lst_tkn->content)));
			ft_tkn_proc_arg(cnt, new_command, lst_tkn);
		}
		if (cnt->flag == 2)
			new_command->specs = ft_strdup(lst_tkn->content);
		if (cnt->flag == 3)
			ft_comm_processing(&lst_tkn, cnt, &lst_redir);
		if (lst_tkn)
			lst_tkn = lst_tkn->next;
		cnt->count_drop_token++;
	}
	new_command->arg = ft_get_ararg_is_lstarg(lst_arg);
	ft_lstclear(&lst_arg, free);
	new_command->lst_redir = lst_redir;
	return (new_command);
}

t_comm	*ft_get_command(t_count *cnt, t_list *lst_token, t_data *data)
{
	t_comm	*new_command;

	new_command = NULL;
	lst_token = ft_get_pos_list_token(cnt->count_drop_token, lst_token);
	new_command = ft_parse_token_for_comm(cnt, lst_token, data);
	cnt->k = 0;
	ft_get_number_lst_redir(new_command->lst_redir);
	return (new_command);
}

t_list	*ft_get_list_comm(t_data *data, t_list *lst_token)
{
	int		i;
	t_count	cnt;
	t_list	*new_lst_comm;
	t_comm	*command;

	i = 0;
	new_lst_comm = NULL;
	command = NULL;
	ft_init_count(&cnt);
	while (i < (data->count_pipe + 1))
	{
		cnt.z = 0;
		cnt.flag = 1;
		command = ft_get_command(&cnt, lst_token, data);
		ft_lstadd_back(&new_lst_comm, ft_lstnew(command));
		i++;
	}
	return (new_lst_comm);
}
