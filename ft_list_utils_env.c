/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:11:50 by dduck             #+#    #+#             */
/*   Updated: 2021/07/29 11:11:52 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst_env	*ft_lstlast_env(t_lst_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_lst_env **lst, t_lst_env *new)
{
	t_lst_env	*back;

	if (!lst || !new)
		return ;
	if (*lst)
	{
		back = ft_lstlast_env(*lst);
		back->next = new;
		new->prev = back;
		new->next = NULL;
	}
	else
		*lst = new;
}

t_lst_env	*ft_init_lst_env(char *cont_env)
{
	t_lst_env	*new_elem;

	new_elem = ft_calloc(1, sizeof(t_lst_env));
	if (!new_elem)
		return (NULL);
	if (cont_env)
		new_elem->env = ft_strdup(cont_env);
	new_elem->next = NULL;
	new_elem->prev = NULL;
	return (new_elem);
}

t_lst_env	*ft_refresh_env_of_arrenv(t_data *data)
{
	t_lst_env	*tmp_lst_env;

	ft_free_lst_env(&data->lst_env);
	data->lst_env = ft_get_envlist_of_envarr(data->my_env, data);
	tmp_lst_env = data->lst_env;
	return (tmp_lst_env);
}

void	ft_free_env_struct(t_lst_env *lst_env)
{
	ft_free_ptr(lst_env->key);
	ft_free_ptr(lst_env->val);
	ft_free_ptr(lst_env->env);
}
