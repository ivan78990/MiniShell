/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:08:29 by ivan              #+#    #+#             */
/*   Updated: 2020/11/18 17:54:09 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int			sign;
	long long	result;
	size_t		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] && (str[i] == '\f' || str[i] == '\t' || str[i] == ' '
			|| str[i] == '\n' || str[i] == '\r' || str[i] == '\v'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if ((result > 9223372036854775807) && (sign == 1))
			return (-1);
		if ((result > 9223372036854775807) && (sign == -1))
			return (0);
		result = result * 10 + str[i++] - '0';
	}
	return (result * sign);
}
