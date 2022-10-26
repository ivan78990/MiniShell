/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:59:05 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:59:06 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putnstr(char *str, int n, int fd)
{
	int		i;

	i = -1;
	if (n < 0)
	{
		while (str[++i] && i < (int)ft_strlen(str) + n)
			ft_putchar_fd(str[i], fd);
	}
	else
	{
		while (str[++i] && i < n)
			ft_putchar_fd(str[i], fd);
	}
}
