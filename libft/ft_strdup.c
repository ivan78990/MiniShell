/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:14:24 by ivan              #+#    #+#             */
/*   Updated: 2020/11/16 13:02:49 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	i;
	char	*istr;

	i = 0;
	istr = (char *)malloc(sizeof(char) * ft_strlen((char *)str) + 1);
	if (istr == NULL)
		return (NULL);
	while (str[i])
	{
		istr[i] = str[i];
		i++;
	}
	istr[i] = 0;
	return (istr);
}
