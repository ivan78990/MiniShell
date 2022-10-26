/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_and_read_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:40:01 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:40:03 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tolower_str(char *str)
{
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(str);
	while (i < size)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

void	er_message(int fd, char *name_file)
{
	char	*er;

	if (fd == -1)
	{
		write(2, "minishell: ", 12);
		er = strerror(errno);
		er = ft_strdup(er);
		er = tolower_str(er);
		write(2, er, ft_strlen(er));
		write(2, ": ", 2);
		write(2, name_file, ft_strlen(name_file));
		write(2, "\n", 1);
		g_global.return_value = 1;
	}
}

int	open_read(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	er_message(fd, name);
	return (fd);
}

int	open_add(char *name)
{
	int	fd;

	fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	er_message(fd, name);
	return (fd);
}

int	open_stop(char *name)
{
	int	fd;

	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	er_message(fd, name);
	return (fd);
}
