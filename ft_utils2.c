/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:06:44 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 12:06:48 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_count_pipe(t_list *lst_token)
{
	int	count_pipe;

	count_pipe = 0;
	while (lst_token)
	{
		if (!ft_strcmp(lst_token->content, "|"))
			count_pipe++;
		lst_token = lst_token->next;
	}
	return (count_pipe);
}

char	*ft_get_val_for_key(t_lst_env *lst_env, char *key)
{
	char	*val;

	while (lst_env)
	{
		if (!ft_strcmp(lst_env->key, key))
		{
			val = ft_strdup(lst_env->val);
			return (val);
		}
		lst_env = lst_env->next;
	}
	return (NULL);
}

void	ft_write_new_shlvl(t_lst_env *lst_env)
{
	t_lst_env	*tmp_env3;

	tmp_env3 = ft_init_lst_env("SHLVL=1");
	ft_parse_env(tmp_env3);
	ft_lstadd_back_env(&lst_env, tmp_env3);
}

void	ft_up_shlvl(t_lst_env *lst_env, t_data *data)
{
	int		new_shlvl_int;
	char	*val_shlvl;
	char	*new_shlvl_str_val;
	char	*tmp_env;
	char	*tmp_env_full_str;

	val_shlvl = ft_get_val_for_key(lst_env, "SHLVL");
	if (!val_shlvl)
	{
		ft_put_error("Not SHLVL in ENV", 0);
		ft_write_new_shlvl(lst_env);
		data->count_env++;
		val_shlvl = ft_get_val_for_key(lst_env, "SHLVL");
	}
	new_shlvl_int = ft_atoi(val_shlvl) + 1;
	new_shlvl_str_val = ft_itoa(new_shlvl_int);
	tmp_env = ft_strjoin("=", new_shlvl_str_val);
	tmp_env_full_str = ft_strjoin("SHLVL", tmp_env);
	ft_get_new_lst_env(data, tmp_env_full_str, "SHLVL", new_shlvl_str_val);
	ft_free_ptr(val_shlvl);
	ft_free_ptr(new_shlvl_str_val);
	ft_free_ptr(tmp_env);
	ft_free_ptr(tmp_env_full_str);
}

void	ft_free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}
