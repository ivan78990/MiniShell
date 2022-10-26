/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivan <ivan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:34:44 by ivan              #+#    #+#             */
/*   Updated: 2020/11/17 12:08:42 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sym_in(char a, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == a)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	beg;
	size_t	kon;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	beg = 0;
	while (s1[beg] && ft_sym_in(s1[beg], set))
		beg++;
	kon = ft_strlen((char *)s1);
	while (kon > beg && ft_sym_in(s1[kon - 1], set))
		kon--;
	str = (char *)malloc(sizeof(*s1) * (kon - beg + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (beg < kon)
	{
		str[i] = s1[beg];
		i++;
		beg++;
	}
	str[i] = 0;
	return (str);
}
