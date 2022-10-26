/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:10:20 by dduck             #+#    #+#             */
/*   Updated: 2021/07/29 11:10:23 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_dollar(t_count *cnt, int *i, char *str)
{
	ft_init_count(cnt);
	cnt->j = *i;
	i = ft_get_posenv(str, i);
	return (*i);
}

void	ft_init_count(t_count *count)
{
	count->i = -1;
	count->j = 0;
	count->k = 0;
	count->z = 0;
	count->start = 0;
	count->len = 0;
	count->flag = 0;
	count->count_drop_token = 0;
	count->count_drop_token_redir = 0;
}

t_data	*ft_init_data(char **env)
{
	t_data	*data_temp;

	data_temp = ft_calloc(1, sizeof (t_data));
	data_temp->count_env = 0;
	data_temp->my_env = NULL;
	data_temp->lst_env = NULL;
	data_temp->count_pipe = 0;
	data_temp->flag_end = 0;
	data_temp->ret = 0;
	data_temp->count_env = ft_size_double_arr(env);
	return (data_temp);
}

int	ft_get_counttoken(t_list *token)
{
	int	count;

	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_comm	*ft_init_command_struct(void)
{
	t_comm	*new_command;

	new_command = NULL;
	new_command = ft_calloc(1, sizeof(t_comm));
	new_command->command = NULL;
	new_command->arg = NULL;
	new_command->flag_nonarg = 1;
	new_command->specs = NULL;
	new_command->lst_redir = NULL;
	new_command->pid = 0;
	new_command->fd_read = 0;
	new_command->fd_write = 1;
	new_command->flag_after_redir = 0;
	return (new_command);
}
