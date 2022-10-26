/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:46:58 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:47:01 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_check_str(char *args)
{
	int		i;
	int		separ;
	char	*key;
	char	*pos_equals;

	i = -1;
	pos_equals = NULL;
	pos_equals = ft_strchr(args, '=');
	if (pos_equals)
	{
		separ = pos_equals - args;
		key = ft_substr(args, 0, separ);
	}
	else
		key = ft_strdup(args);
	while (key[++i])
	{
		if (ft_strchr(("<>;-=+~?)(\\|"), key[i]))
		{
			ft_free_ptr(key);
			return (0);
		}
	}
	ft_free_ptr(key);
	return (1);
}

int	ft_export_check(char **args, int i)
{
	if (!ft_isalpha(args[i][0]) && args[i][0] != '_')
		return (0);
	if (!ft_export_check_str(args[i]))
		return (0);
	return (1);
}
