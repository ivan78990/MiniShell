/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:44:54 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:44:56 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_revers_env(t_lst_env *lst_env1, t_lst_env *lst_env2)
{
	char	*key;
	char	*val;
	char	*env;

	key = lst_env1->key;
	val = lst_env1->val;
	env = lst_env1->env;
	lst_env1->key = lst_env2->key;
	lst_env1->val = lst_env2->val;
	lst_env1->env = lst_env2->env;
	lst_env2->val = val;
	lst_env2->key = key;
	lst_env2->env = env;
}

t_lst_env	*ft_sort_env(t_lst_env *lst_env)
{
	t_lst_env	*lst_env1;
	t_lst_env	*lst_env2;

	if (!lst_env)
		return (NULL);
	lst_env1 = lst_env;
	while (lst_env1)
	{
		lst_env2 = lst_env1->next;
		while (lst_env2)
		{
			if (ft_strncmp(lst_env1->key, lst_env2->key,
					ft_strlen(lst_env1->key) + 1) > 0)
			{
				ft_revers_env(lst_env1, lst_env2);
			}
			lst_env2 = lst_env2->next;
		}
		lst_env1 = lst_env1->next;
	}
	lst_env1 = NULL;
	return (lst_env);
}

void	ft_get_pwf_env(t_lst_env *lst_env)
{
	char	*pwd;
	char	buff[4097];
	char	*tmp1_env;
	char	*tmp2_env;

	pwd = getcwd(buff, 4096);
	tmp1_env = ft_strjoin("PWD", "=");
	tmp2_env = ft_strjoin(tmp1_env, pwd);
	lst_env->env = ft_strdup(tmp2_env);
	ft_parse_env(lst_env);
	ft_free_ptr(tmp1_env);
	ft_free_ptr(tmp2_env);
}

t_lst_env	*ft_get_lst_ienv(t_data *data)
{
	t_lst_env	*lst_env;
	t_lst_env	*tmp_env1;
	t_lst_env	*tmp_env2;
	t_lst_env	*tmp_env3;

	lst_env = NULL;
	tmp_env1 = NULL;
	tmp_env2 = NULL;
	tmp_env3 = NULL;
	tmp_env1 = ft_init_lst_env("OLDPWD");
	ft_parse_env(tmp_env1);
	ft_lstadd_back_env(&lst_env, tmp_env1);
	tmp_env2 = ft_init_lst_env("PWD");
	ft_get_pwf_env(tmp_env2);
	ft_lstadd_back_env(&lst_env, tmp_env2);
	tmp_env3 = ft_init_lst_env("SHLVL=1");
	ft_parse_env(tmp_env3);
	ft_lstadd_back_env(&lst_env, tmp_env3);
	data->count_env = 3;
	return (lst_env);
}

t_lst_env	*ft_lst_env_del_elem(t_lst_env *lst_before, t_lst_env *lst_env)
{
	t_lst_env	*lst_ret;

	lst_ret = NULL;
	lst_before->next = lst_env->next;
	ft_free_env_struct(lst_env);
	ft_free_ptr(lst_env);
	return (lst_ret);
}
