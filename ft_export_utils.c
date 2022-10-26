/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:18:22 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:18:25 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Берет из строки env значения key и val, если нет val - пишет NULL
void	ft_get_keyval_lst_env(char *new_str_env, char **new_key, char **new_val)
{
	int		ravno;
	int		len_new_env;
	char	*ch_tmp;

	len_new_env = (int)ft_strlen(new_str_env);
	ch_tmp = ft_strchr(new_str_env, '=');
	if (ch_tmp)
	{
		ravno = ch_tmp - new_str_env;
		*new_key = ft_substr(new_str_env, 0, ravno);
		*new_val = ft_substr(new_str_env, ravno + 1, len_new_env - 1);
	}
	else
	{
		*new_key = ft_strdup(new_str_env);
		*new_val = NULL;
	}
}

void	ft_exprt_prcssr(t_lst_env *lst_env, char *key, char *val, char *str_env)
{
	ft_free_ptr(lst_env->env);
	ft_free_ptr(lst_env->key);
	if (lst_env->val)
		ft_free_ptr(lst_env->val);
	lst_env->key = ft_strdup(key);
	if (val)
		lst_env->val = ft_strdup(val);
	else
		lst_env->val = NULL;
	lst_env->env = ft_strdup(str_env);
}

// Устанавливает по key - val
void	ft_get_new_lst_env(t_data *data, char *str_env, char *key, char *val)
{
	int			flag_change_env;
	t_lst_env	*new_struct_env;
	t_lst_env	*tmp_lst_env;

	new_struct_env = NULL;
	tmp_lst_env = NULL;
	flag_change_env = 0;
	tmp_lst_env = data->lst_env;
	while (tmp_lst_env)
	{
		if (!ft_strcmp(tmp_lst_env->key, key))
		{
			ft_exprt_prcssr(tmp_lst_env, key, val, str_env);
			flag_change_env = 1;
		}
		tmp_lst_env = tmp_lst_env->next;
	}
	if (!flag_change_env)
	{
		new_struct_env = ft_init_lst_env(str_env);
		ft_parse_env(new_struct_env);
		data->count_env++;
	}
	ft_lstadd_back_env(&data->lst_env, new_struct_env);
}

// перезапись arr_env из lst_env
void	ft_rewrite_arr_env(t_data *data, char *env)
{
	char	*key;
	char	*val;
	char	**new_arr_env;
	char	*new_env;

	key = NULL;
	val = NULL;
	new_arr_env = NULL;
	new_env = NULL;
	new_env = ft_strdup(env);
	ft_get_keyval_lst_env(new_env, &key, &val);
	ft_get_new_lst_env(data, new_env, key, val);
	ft_free_arr(data->my_env);
	new_arr_env = ft_get_envarr_of_envlst(data->lst_env, data);
	data->my_env = new_arr_env;
	ft_free_ptr(key);
	ft_free_ptr(val);
	ft_free_ptr(new_env);
}
