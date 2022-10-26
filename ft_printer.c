/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:08:22 by dduck             #+#    #+#             */
/*   Updated: 2021/07/29 11:08:25 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export_key(t_lst_env *tmp_lst_env, int in_fd)
{
	ft_putstr_fd("=\"", in_fd);
	ft_putstr_fd(tmp_lst_env->val, in_fd);
	ft_putstr_fd("\"", in_fd);
}

int	ft_put_error(char *str, int flag_ret)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	if (flag_ret)
		return (flag_ret);
	return (0);
}

//Создает с arr_env временный лист, сортирует его, печатает и зачищает
void	ft_print_export(t_data *data, int in_fd)
{
	t_lst_env	*start_tmp_lst;
	t_lst_env	*tmp_lst_env;

	tmp_lst_env = NULL;
	tmp_lst_env = ft_get_envlist_of_envarr(data->my_env, data);
	if (!tmp_lst_env)
		return ;
	tmp_lst_env = ft_sort_env(tmp_lst_env);
	start_tmp_lst = tmp_lst_env;
	while (tmp_lst_env)
	{
		if (ft_strcmp(tmp_lst_env->key, "?"))
		{
			if (tmp_lst_env->key)
			{
				ft_putstr_fd("declare -x ", in_fd);
				ft_putstr_fd(tmp_lst_env->key, in_fd);
			}
			if (tmp_lst_env->val)
				ft_print_export_key(tmp_lst_env, in_fd);
			ft_putstr_fd("\n", in_fd);
		}
		tmp_lst_env = tmp_lst_env->next;
	}
	ft_free_lst_env(&start_tmp_lst);
}

t_list	*ft_put_syntax_error(char *str_error)
{
	ft_put_error(str_error, 0);
	g_global.return_value = 258;
	return (NULL);
}
