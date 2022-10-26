/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:38:28 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:38:30 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_mini(char **args, long ret_exit)
{
	if (args[0])
	{
		if (ft_isalpha(args[0][0]) || ft_strlen(args[0]) > 20)
		{
			ft_putendl_fd("minishell: exit : numeric argument required", 2);
			exit(255);
		}
		else
		{
			ret_exit = ft_atoi(args[0]);
			if (ret_exit == -1)
			{
				ft_putendl_fd("exit", 1);
				g_global.return_value = 255;
				exit(255);
			}
			ft_putendl_fd("exit", 1);
			g_global.return_value = ret_exit;
			exit(ret_exit);
		}
	}
	return (ret_exit);
}

void	exit_max(char **args, int ret_exit, int i)
{
	if (args[0])
	{
		while (args[0][++i])
		{
			if ((args[0][i] >= 'a' && args[0][i] <= 'z'))
			{
				ft_putendl_fd("minishell: exit : numeric argument required", 2);
				exit(255);
			}
		}
		exit_mini(args, ret_exit);
		if (!ft_strcmp(args[0], "9223372036854775808"))
		{
			ft_putendl_fd("exit", 1);
			g_global.return_value = 255;
			exit(255);
		}
		if (!ft_strcmp(args[0], "-9223372036854775808"))
		{
			ft_putendl_fd("exit", 1);
			g_global.return_value = 0;
			exit(255);
		}
	}
}

int	ft_exit(char **args)
{
	long int	ret_exit;
	int			i;

	i = -1;
	ret_exit = 0;
	if (args[0])
	{
		if (args[1])
		{
			ft_putendl_fd("exit", 1);
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			g_global.return_value = 1;
			return (1);
		}
	}
	exit_max(args, ret_exit, i);
	ft_putendl_fd("exit", 1);
	g_global.return_value = ret_exit;
	exit(ret_exit);
}

int	ft_pwd(t_comm *comm)
{
	char	cwd[4097];

	ft_putstr_fd(getcwd(cwd, 4096), comm->fd_write);
	ft_putchar_fd('\n', comm->fd_write);
	g_global.return_value = 0;
	return (1);
}

int	ft_print_env(t_data *data, t_comm *comm, char **args)
{
	if (!args[0])
	{
		print_env(data, comm->fd_write);
		g_global.return_value = 0;
	}
	else
	{
		ft_putstr_fd("env: ", comm->fd_write);
		ft_putstr_fd(args[1], comm->fd_write);
		ft_putstr_fd(": No such file or directory", comm->fd_write);
		ft_putchar_fd('\n', comm->fd_write);
		g_global.return_value = 127;
	}
	return (1);
}
