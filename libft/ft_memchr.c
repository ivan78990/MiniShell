/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:29:02 by warchang          #+#    #+#             */
/*   Updated: 2020/11/16 13:02:49 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	p;

	i = 0;
	p = (char)c;
	while (i < n)
	{
		if (((unsigned char *)arr)[i] == p)
			return ((unsigned char *)arr + i);
		i++;
	}
	return (NULL);
}
