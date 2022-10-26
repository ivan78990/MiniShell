/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:39:02 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:39:04 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_data *data, int fd)
{
	int		i;

	i = -1;
	while (data->my_env[++i])
	{
		if ((data->my_env[i][0] != '?') && (ft_strchr(data->my_env[i], '=')))
			ft_putendl_fd(data->my_env[i], fd);
	}
}

t_lst_env	*ft_find_unset(t_lst_env *lst_env, t_lst_env *lst_strt, char *key)
{
	t_lst_env	*tmp_lst_bef;

	while (lst_env)
	{
		if (!ft_strcmp(key, lst_env->key) && lst_env == lst_strt)
		{
			lst_env = ft_lst_env_del_head(lst_env);
			lst_strt = lst_env;
			break ;
		}
		tmp_lst_bef = lst_env;
		lst_env = lst_env->next;
		if (lst_env && (!ft_strcmp(key, lst_env->key)))
		{
			ft_lst_env_del_elem(tmp_lst_bef, lst_env);
			break ;
		}
	}
	return (lst_strt);
}

void	ft_check_env_for_unset(t_lst_env *lst_env, char **args, t_data *data)
{
	int			i;
	char		*key;
	t_lst_env	*tmp_lst_start;

	tmp_lst_start = lst_env;
	i = 0;
	while (args[i])
	{
		lst_env = tmp_lst_start;
		key = ft_strdup(args[i]);
		tmp_lst_start = ft_find_unset(lst_env, tmp_lst_start, key);
		ft_free_ptr(key);
		i++;
	}
	data->lst_env = tmp_lst_start;
}

int	unset_built(char **args, t_data *data)
{
	int			i;
	t_lst_env	*tmp_lst_env;

	if (!args[0])
		return (1);
	i = -1;
	while (args[++i])
	{
		if (args[i])
		{
			if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
			{
				ft_putendl_fd("export: not a valid identifier", 2);
				g_global.return_value = 1;
				return (1);
			}
		}
	}
	tmp_lst_env = ft_refresh_env_of_arrenv(data);
	ft_check_env_for_unset(tmp_lst_env, args, data);
	ft_free_arr(data->my_env);
	data->my_env = ft_get_envarr_of_envlst(data->lst_env, data);
	g_global.return_value = 1;
	return (1);
}
