/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:55:21 by warchang          #+#    #+#             */
/*   Updated: 2021/04/22 19:04:50 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	size_t	result;
	char	*ptr;

	result = 0;
	if (!str)
		return (0);
	ptr = (char *)str;
	while (ptr[result])
		result++;
	return (result);
}

char	*my_strjoin(char *s1, char *s2)
{
	char	*result;
	int		j;

	if (!s2)
		return (NULL);
	result = (char *)malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * sizeof
			(char));
	if (result)
	{
		j = 0;
		if (s1)
			gnl_strlcpy(result, s1, gnl_strlen(s1) + 1);
		while (*(s2 + j))
		{
			result[gnl_strlen(s1) + j] = *(s2 + j);
			j++;
		}
		result[gnl_strlen(s1) + j] = 0;
	}
	if (s1)
		free(s1);
	return (result);
}

char	*buff_trim(char *buff, size_t len)
{
	char	*result;
	size_t	i;

	if (!buff)
		return (NULL);
	result = (char *)malloc((gnl_strlen(buff) - len + 1) * sizeof(char));
	if (result)
	{
		i = 0;
		while (buff[len + i] != 0)
		{
			result[i] = *(buff + len + i);
			i++;
		}
		result[i] = 0;
	}
	if (buff)
		free(buff);
	return (result);
}

void	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	if (!dest || !src)
		return ;
	if (size == 0)
		return ;
	if (dest || src)
	{
		while ((size > 1) && *src != 0)
		{
			*dest++ = *src++;
			size--;
		}
		*dest = 0;
	}
}
