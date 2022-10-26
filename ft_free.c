/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:18:47 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:18:48 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst_env(t_lst_env **lst_env)
{
	t_lst_env	*tmp;
	t_lst_env	*one;

	if (!lst_env)
		return ;
	one = *lst_env;
	while (one)
	{
		tmp = one->next;
		ft_free_env_struct(one);
		ft_free_ptr(one);
		one = tmp;
	}
	*lst_env = NULL;
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = -1;
	if (arr)
	{
		while (arr[++i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		free(arr);
		arr = NULL;
	}
}

void	ft_free_redir_str(void *redir_strct)
{
	t_redir	*tmp;

	tmp = redir_strct;
	ft_free_ptr(tmp->filename);
	ft_free_ptr(tmp);
}

void	ft_free_comm_strct(void *comm_strct)
{
	t_comm	*tmp;

	tmp = comm_strct;
	ft_free_ptr(tmp->command);
	ft_free_arr(tmp->arg);
	ft_free_ptr(tmp->specs);
	ft_free_ptr(tmp);
}

void	ft_free_lst_comm(t_list *lst_comm)
{
	if (lst_comm)
		ft_lstclear(&lst_comm, ft_free_comm_strct);
}
