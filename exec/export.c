/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:38:17 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:38:18 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	var_position(char *key, t_data *data)
{
	int		i;
	char	*tmp;
	char	*tmp_bez_ravno;

	i = -1;
	while (data->my_env[++i])
	{
		tmp = ft_strjoinch(key, '=');
		tmp_bez_ravno = ft_strdup(key);
		if (ft_strstartswith(data->my_env[i], tmp))
		{
			ft_free_ptr(tmp);
			return (i);
		}
		if (!ft_strcmp(tmp_bez_ravno, data->my_env[i]))
		{
			ft_free_ptr(tmp_bez_ravno);
			return (i);
		}
		ft_free_ptr(tmp);
		ft_free_ptr(tmp_bez_ravno);
	}
	return (i);
}

char	*env_val(char *var, t_data *data)
{
	int		i;
	char	*new;

	i = -1;
	while (data->my_env[++i])
	{
		new = ft_strjoinch(var, '=');
		if (ft_strstartswith(data->my_env[i], new))
		{
			free(new);
			return (ft_strchr(data->my_env[i], '=') + 1);
		}
		free(new);
	}
	return (NULL);
}

char	**realloc_envv(int new_size, t_data *data)
{
	char	**new;
	int		i;

	new = (char **)ft_memalloc(sizeof(char *) * (new_size + 1));
	i = -1;
	while (data->my_env[++i] && i < new_size)
	{
		new[i] = ft_strdup(data->my_env[i]);
		ft_free_ptr(data->my_env[i]);
	}
	ft_free_ptr(data->my_env);
	new[i] = NULL;
	return (new);
}

void	new_val(char *key, char *value, t_data *data)
{
	int		pos;
	char	*tmp;

	pos = var_position(key, data);
	tmp = ft_strjoin("=", value);
	if (data->my_env[pos])
	{
		free(data->my_env[pos]);
		if (value)
			data->my_env[pos] = ft_strjoin(key, tmp);
		else
			data->my_env[pos] = ft_strjoin(key, "=");
	}
	else
	{
		data->my_env = realloc_envv(pos + 1, data);
		if (value)
			data->my_env[pos] = ft_strjoin(key, tmp);
		else
			data->my_env[pos] = ft_strjoin(key, "=");
	}
	free(tmp);
}

int	export(char **args, t_data *data, int in_fd)
{
	int		i;

	if (!args[0])
	{
		ft_print_export(data, in_fd);
		return (1);
	}
	i = -1;
	while (args[++i])
	{
		if (args[i])
		{
			if (!(ft_export_check(args, i)))
			{
				ft_putendl_fd("export: not a valid identifier", 2);
				g_global.return_value = 1;
				return (1);
			}
		}
		ft_rewrite_arr_env(data, args[i]);
	}
	g_global.return_value = 0;
	return (1);
}
