/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 14:29:41 by warchang          #+#    #+#             */
/*   Updated: 2021/04/22 19:28:04 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	mycheck_int(int fd, char **line)
{
	char	temp[1];

	if (fd < 0)
		return (0);
	if ((read(fd, temp, 0)) < 0)
		return (0);
	if (!line)
		return (0);
	return (1);
}

int	nlbuff(char *buff)
{
	int	i;

	if (buff)
	{
		i = 0;
		while (buff[i])
		{
			if (buff[i] == '\n')
				return (1);
			i++;
		}
	}
	return (0);
}

char	*linefrom_buff(char *buff)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = 0;
	while (buff[len] != '\n' && buff[len] != 0)
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res)
	{
		i = 0;
		while (i < len)
		{
			res[i] = buff[i];
			i++;
		}
		res[i] = 0;
	}
	return (res);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff = NULL;

	if (!mycheck_int(fd, line))
		return (-1);
	buff = start_buff_init(buff, fd);
	if (!buff)
		return (-1);
	if (nlbuff(buff))
	{
		*line = linefrom_buff(buff);
		if (*line)
		{
			buff = buff_trim(buff, gnl_strlen(*line) + 1);
			if (buff)
				return (1);
		}
		free(buff);
		return (-1);
	}
	*line = my_strjoin(buff, "\0");
	buff = NULL;
	return (0);
}

char	*start_buff_init(char *buff, int fd)
{
	char	*buff1;
	int		ret;

	buff1 = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buff1)
	{
		while (!nlbuff(buff))
		{
			ret = read(fd, buff1, BUFFER_SIZE);
			if (ret > 0)
			{
				buff1[ret] = 0;
				buff = my_strjoin(buff, buff1);
			}
		}
		if (!buff)
			buff = my_strjoin(buff, "\0");
		free(buff1);
		buff1 = NULL;
		return (buff);
	}
	return (NULL);
}
