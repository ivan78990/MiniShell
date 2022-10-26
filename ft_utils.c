/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:17:30 by dduck             #+#    #+#             */
/*   Updated: 2021/07/29 11:17:32 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_size_double_arr(char **arr)
{
	int		i;
	size_t	size;

	i = -1;
	size = 0;
	if (!arr)
		return (0);
	while (arr[++i])
		size++;
	return (size);
}

void	ft_refresh_dollar_quest(t_data *data)
{
	char	*str_ret;

	str_ret = ft_itoa(g_global.return_value);
	ft_new_val_for_key(data, "?", str_ret);
	ft_free_ptr(str_ret);
}
