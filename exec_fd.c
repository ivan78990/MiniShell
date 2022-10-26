/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:40:53 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:40:54 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_check(int sig)
{
	if (sig == SIGINT)
		exit(1);
	if (sig == SIGQUIT)
		return ;
}

void	write_and_read_stop(char *s_word, int *fd)
{
	int		fl;
	char	*str;

	signal(SIGINT, signal_check);
	signal(SIGQUIT, signal_check);
	fl = 1;
	while (fl)
	{
		write(1, "> ", 2);
		if (!get_next_line(0, &str))
			exit (0);
		fl = ft_strncmp(s_word, str, ft_strlen(s_word));
		if (!fl)
		{
			free(str);
			exit (0);
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
	}
}

int	error_drr(int flag, int *fd, int status)
{
	if (flag == 1)
		perror("minishell");
	if (flag == 2)
	{
		close(fd[1]);
		close(fd[0]);
		g_global.return_value = WEXITSTATUS(status);
	}
	return (-1);
}

int	dub_rev_redir(char *stop_word)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) == -1)
	{
		return (error_drr(1, NULL, 0));
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell");
		kill(0, SIGKILL);
	}
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 1)
		return (error_drr(2, NULL, 0));
	if (pid == 0)
	{
		close(fd[0]);
		write_and_read_stop(stop_word, fd);
	}
	close(fd[1]);
	return (fd[0]);
}
