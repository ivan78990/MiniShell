/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:20:30 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:20:31 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tkn_proc_arg(t_count *cnt, t_comm *comm, t_list *tkn)
{
	if (!cnt->z)
		cnt->z++;
	if (!cnt->k)
	{
		comm->command = ft_strdup(tkn->content);
		cnt->k = 1;
	}
	else
	{
		comm->cnt_arg++;
		comm->flag_nonarg = 0;
		cnt->z++;
	}
}

char	**ft_get_ararg_is_lstarg(t_list *lst_arg)
{
	char	**new_ar_arg;
	int		len_lst_arg;
	int		i;

	i = 0;
	len_lst_arg = ft_lstsize(lst_arg);
	new_ar_arg = ft_calloc(len_lst_arg + 1, sizeof (char *));
	while (lst_arg)
	{
		new_ar_arg[i] = ft_strdup(lst_arg->content);
		lst_arg = lst_arg->next;
		i++;
	}
	new_ar_arg[i] = NULL;
	return (new_ar_arg);
}

void	ft_comm_processing(t_list **lst_tkn, t_count *cnt, t_list **lst_rdr)
{
	*lst_rdr = ft_get_list_redirect(*lst_tkn, cnt);
	*lst_tkn = ft_get_pos_list_token(cnt->count_drop_token_redir, *lst_tkn);
	cnt->count_drop_token += cnt->count_drop_token_redir;
	cnt->count_drop_token_redir = 0;
}
