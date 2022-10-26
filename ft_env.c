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

char	**ft_get_envarr_of_envlst(t_lst_env *first_lstenv, t_data *data)
{
	char	**arr_env;
	int		i;

	i = 0;
	if (!first_lstenv)
		return (NULL);
	arr_env = ft_calloc(data->count_env + 1, (sizeof (char *)));
	if (!arr_env)
		exit(1);
	while (first_lstenv)
	{
		arr_env[i] = ft_strdup(first_lstenv->env);
		first_lstenv = first_lstenv->next;
		i++;
	}
	return (arr_env);
}

// берет из env.env и парсит в key и val по "="
int	ft_parse_env(t_lst_env *env)
{
	int		ravno;
	int		len_val;
	char	*ch_tmp;

	len_val = (int)ft_strlen(env->env);
	ch_tmp = ft_strchr(env->env, '=');
	if (ch_tmp)
	{
		ravno = ch_tmp - env->env;
		env->key = ft_substr(env->env, 0, ravno);
		env->val = ft_substr(env->env, ravno + 1, len_val - 1);
	}
	else
		env->key = ft_strdup(env->env);
	return (0);
}

t_lst_env	*ft_get_envlist_of_envarr(char **ev, t_data *data)
{
	int			i;
	t_lst_env	*env_list;
	t_lst_env	*tmp_env;

	env_list = NULL;
	tmp_env = NULL;
	if (!ev)
		return (NULL);
	i = -1;
	data->count_env = ft_size_double_arr(ev);
	while (ev[++i])
	{
		tmp_env = ft_init_lst_env(ev[i]);
		ft_parse_env(tmp_env);
		ft_lstadd_back_env(&env_list, tmp_env);
	}
	data->count_env = i;
	return (env_list);
}

char	*ft_get_env_of_keyval(char *key, char *val)
{
	char	*new_env;
	char	*tmp_env;

	if (val)
	{
		tmp_env = ft_strjoin(key, "=");
		new_env = ft_strjoin(tmp_env, val);
		ft_free_ptr(tmp_env);
	}
	else
		new_env = ft_strdup(key);
	return (new_env);
}

void	ft_new_val_for_key(t_data *data, char *key, char *val)
{
	t_lst_env	*new_lst_env;

	new_lst_env = ft_refresh_env_of_arrenv(data);
	while (new_lst_env)
	{
		if (!ft_strcmp(key, new_lst_env->key))
		{
			ft_free_env_struct(new_lst_env);
			new_lst_env->key = ft_strdup(key);
			new_lst_env->val = ft_strdup(val);
			new_lst_env->env = ft_get_env_of_keyval(key, val);
		}
		new_lst_env = new_lst_env->next;
	}
	ft_free_arr(data->my_env);
	data->my_env = ft_get_envarr_of_envlst(data->lst_env, data);
}
