/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 15:42:53 by warchang          #+#    #+#             */
/*   Updated: 2020/11/18 18:39:40 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

int	ft_check(char *str, long *n)
{
	if (*n == 0)
	{
		str[0] = 48;
		return (0);
	}
	if (*n < 0)
	{
		str[0] = '-';
		*n = *n * -1;
	}
	return (1);
}

/*
// Need check after NORMINETTE!
*/
char	*ft_itoa(int nb)
{
	int		i;
	char	*str;
	long	n;

	n = nb;
	i = len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (!ft_check(str, &n))
		return (str);
	while (n > 0)
	{
		str[i--] = 48 + (n % 10);
		n = n / 10;
	}
	return (str);
}
