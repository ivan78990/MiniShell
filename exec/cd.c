/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 10:37:29 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 10:37:43 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	real_path(char *path, t_data *data)
{
	char	*home;

	home = path_home(path, 0, data);
	ft_putstr(home);
	free(home);
}

void	change_directory(char *path, int new_path, t_data *data)
{
	char	*current;
	char	str[4097];

	current = getcwd(str, 4096);
	if (!chdir(path))
	{
		if (new_path)
		{
			real_path(path, data);
			ft_putchar('\n');
		}
		new_val("OLDPWD", current, data);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		if (access(path, F_OK) == -1)
			ft_putstr_fd("no such file or directory: ", 2);
		else if (access(path, R_OK) == -1)
			ft_putstr_fd("permission denied: ", 2);
		else
			ft_putstr_fd("not a directory: ", 2);
		ft_putendl_fd(path, 2);
		g_global.return_value = 1;
	}
}

static int	more_args(char **args, t_data *data)
{
	char	*current;
	char	str[4096 + 1];
	char	*new;

	if (args[1])
	{
		if (args[2])
		{
			ft_putendl_fd("cd: too many arguments", 2);
			return (1);
		}
		current = getcwd(str, 4096);
		new = ft_strreplace(current, args[0], args[1]);
		if (!new)
		{
			ft_putstr_fd("cd: string not in pwd: ", 2);
			ft_putendl_fd(args[0], 2);
			free(new);
			return (1);
		}
		change_directory(new, 1, data);
		free(new);
		return (1);
	}
	return (0);
}

int	cd_b(char **args, t_data *data)
{
	char	*home;

	home = env_val("HOME", data);
	if (!args[0])
	{
		change_directory(home, 0, data);
		return (1);
	}
	if (more_args(args, data))
		return (1);
	else
	{
		if (!ft_strcmp(args[0], "--"))
		{
			change_directory(home, 0, data);
			return (1);
		}
		else if (args[0][0] == '-' && !args[0][2])
		{
			change_directory(env_val("OLDPWD", data), 1, data);
			return (1);
		}
		change_directory(args[0], 0, data);
	}
	return (1);
}
