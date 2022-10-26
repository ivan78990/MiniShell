/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:40:25 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:40:26 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_text(char *name)
{
	char	*er;

	write(2, "minishell: ", 12);
	er = strerror(errno);
	er = ft_strdup(er);
	er = tolower_str(er);
	write(2, er, ft_strlen(er));
	write(2, ": ", 2);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
	exit(126);
}

void	switch_fd(char *path, t_comm *comm, t_data *data)
{
	if (comm->fd_read >= 0)
		dup2(comm->fd_read, 0);
	if (comm->fd_write >= 0)
		dup2(comm->fd_write, 1);
	if (execve(path, comm->arg, data->my_env) == -1)
		error_text(comm->arg[0]);
}

int	execution1(char *path, t_comm *comm, t_data *data)
{
	pid_t	pid;
	int		ret_value;

	if (exec_fd(comm))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(path);
		perror("minishell");
		ft_putendl("Fork failed to create a new process.");
		kill(0, SIGKILL);
		return (-1);
	}
	if (pid == 0)
		switch_fd(path, comm, data);
	wait(&ret_value);
	if (path)
		free(path);
	g_global.return_value = WEXITSTATUS(ret_value);
	wexitstatus(ret_value);
	return (1);
}

int	execution2(char	*path, t_comm *comm, t_data *data)
{
	int	ret_value;

	if (exec_fd(comm))
		return (-1);
	if (comm->fd_read >= 0 )
		dup2(comm->fd_read, 0);
	if (comm->fd_write >= 0 )
		dup2(comm->fd_write, 1);
	if (execve(path, comm->arg, data->my_env) == -1)
		error_text(comm->arg[0]);
	if (path)
		free(path);
	g_global.return_value = WEXITSTATUS(ret_value);
	wexitstatus(ret_value);
	return (1);
}

int	simplest_exec(t_comm *comm, t_data *data)
{
	struct stat	file;

	if (exec_fd(comm) != 0)
		return (0);
	if (is_builtin(comm, data))
		return (0);
	if (is_bins1(comm, data))
		return (0);
	if (lstat(comm->arg[0], &file) != -1)
	{
		if (file.st_mode & S_IFDIR)
		{
			change_directory(comm->arg[0], 0, data);
			return (0);
		}
		else if (file.st_mode & S_IXUSR)
			return (execution1(ft_strdup(comm->arg[0]), comm, data));
	}
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(comm->arg[0], 2);
	g_global.return_value = 127;
	return (0);
}
