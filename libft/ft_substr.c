/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:18:34 by ivan              #+#    #+#             */
/*   Updated: 2020/11/16 13:02:49 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned char	i;

	i = 0;
	sub = NULL;
	if (!s)
		return (sub);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == sub)
		return (NULL);
	if (start >= ft_strlen((char *)s))
	{
		sub[i] = '\0';
		return (sub);
	}
	while (len)
	{
		sub[i] = s[start];
		i++;
		start++;
		len--;
	}
	sub[i] = '\0';
	return (sub);
}
