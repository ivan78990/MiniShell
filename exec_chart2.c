/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_chart2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:40:37 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:40:39 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_executable(char *path, struct stat f, t_comm *comm, t_data
*data)
{
	if (f.st_mode & S_IFREG)
	{
		if (f.st_mode & S_IXUSR)
			return (execution2(path, comm, data));
		else
		{
			ft_putstr("minishell: permission denied: ");
			ft_putendl(path);
		}
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	is_builtin(t_comm *comm, t_data *data)
{
	if (comm->arg[0])
	{
		if (ft_strequ(comm->arg[0], "exit"))
			return (ft_exit(comm->arg + 1));
		else if (!ft_strcmp(comm->arg[0], "pwd"))
			return (ft_pwd(comm));
		else if (ft_strequ(comm->arg[0], "echo"))
			return (echo_b(comm, comm->fd_write));
		else if (!ft_strcmp(comm->arg[0], "cd"))
			return (cd_b(comm->arg + 1, data));
		else if (!ft_strcmp(comm->arg[0], "export"))
			return (export(comm->arg + 1, data, comm->fd_write));
		else if (!ft_strcmp(comm->arg[0], "unset"))
			return (unset_built(comm->arg + 1, data));
		else if (!ft_strcmp(comm->arg[0], "env"))
			return (ft_print_env(data, comm, comm->arg + 1));
	}
	return (0);
}

int	is_bins(t_comm *comm, t_data *data)
{
	int				i;
	char			*bin_path;
	char			**path;
	struct stat		f;

	path = ft_strsplit(env_val("PATH", data), ':');
	i = -1;
	while (path && path[++i])
	{
		if (ft_strstartswith(comm->arg[0], path[i]))
			bin_path = ft_strdup(comm->arg[0]);
		else
			bin_path = ft_pathjoin(path[i], comm->arg[0]);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
		{
			ft_freestrarr(path);
			return (is_executable(bin_path, f, comm, data));
		}
	}
	ft_freestrarr(path);
	return (0);
}

int	path_for_exec(t_comm *comm, t_data *data, char **path)
{
	int				i;
	char			*bin_path;
	struct stat		f;

	i = -1;
	while (path && path[++i])
	{
		if (ft_strstartswith(comm->arg[0], path[i]))
			bin_path = ft_strdup(comm->arg[0]);
		else
			bin_path = ft_pathjoin(path[i], comm->arg[0]);
		if (lstat(bin_path, &f) == -1)
			free(bin_path);
		else
		{
			ft_freestrarr(path);
			return (execution1(bin_path, comm, data));
		}
	}
	ft_freestrarr(path);
	return (0);
}

int	is_bins1(t_comm *comm, t_data *data)
{
	int				check;
	char			**path;
	char			*tmp;

	if (!comm->command)
		return (0);
	tmp = env_val("PATH", data);
	if (!tmp)
		return (0);
	path = ft_strsplit(tmp, ':');
	check = path_for_exec(comm, data, path);
	return (check);
}
