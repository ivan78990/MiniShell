/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:12:28 by dduck             #+#    #+#             */
/*   Updated: 2021/07/29 11:12:30 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c) || c == '?')
		return (1);
	return (0);
}

char	*ft_grep_env(t_count *cnt, char **env)
{
	char	*tmp4;

	cnt->z = 0;
	while (env[cnt->k][cnt->z] && env[cnt->k][cnt->z] != '=')
		cnt->z++;
	tmp4 = ft_substr(env[cnt->k], 0, cnt->z);
	return (tmp4);
}

int	*ft_get_posenv(char *str, int *i)
{
	while (str[++(*i)])
	{
		if (!ifkey(str[*i]))
			break ;
	}
	return (i);
}

void	ft_check_env(char **env, t_count *cnt, char *tmp)
{
	char	*tmp_key;

	while (env[++cnt->k])
	{
		if (ft_strstr(env[cnt->k], tmp))
		{
			tmp_key = ft_grep_env(cnt, env);
			if (!ft_strcmp(tmp, tmp_key))
			{
				cnt->start = 1;
				ft_free_ptr(tmp_key);
				break ;
			}
			ft_free_ptr(tmp_key);
		}
	}
}
