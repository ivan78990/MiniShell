/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:25:46 by warchang          #+#    #+#             */
/*   Updated: 2020/11/16 13:02:49 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int ch)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	if (ch == 0)
		return ((char *)str + i);
	while (i > 0)
	{
		i--;
		if (str[i] == ch)
			return ((char *)str + i);
	}
	return (NULL);
}
