/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:16:22 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:16:23 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_print(t_comm *comm)
{
	printf("Проверка структуры:\n"
		   "pars_pars comm=%s, flag_nonarg=%d, count_arg=%d, spec=%s\n",
		   comm->command, comm->flag_nonarg, comm->cnt_arg, comm->specs);
	printf("cnt.arg=%d, flag_after=%d\n", comm->cnt_arg,
		   comm->flag_after_redir);
}

void	ft_print_comm(t_list *lst_comm, char *name)
{
	int		i;
	t_comm	*comm;
	t_redir	*redir;
	char	**arr;

	printf("**%s**\n", name);
	while (lst_comm)
	{
		comm = lst_comm->content;
		arr = comm->arg;
		i = -1;
		ft_print_print(comm);
		while (comm->command && ++i <= comm->cnt_arg + 1)
			printf("arg[%d]=%s\n", i, arr[i]);
		while (comm->lst_redir)
		{
			redir = comm->lst_redir->content;
			printf("lst_dir type=%d, lilename=%s\n",
				   redir->type_redir, redir->filename);
			comm->lst_redir = comm->lst_redir->next;
		}
		lst_comm = lst_comm->next;
	}
}

int	ft_print_arr_env(char **arr)
{
	int	i;

	i = -1;
	if (!(arr))
		ft_putstr("Non arr!");
	while (arr[++i])
	{
		printf("arr[%d]=%s\n", i, arr[i]);
	}
	return (0);
}

int	ft_print_token(t_list *token, char *name)
{
	printf("**%s**\n", name);
	while (token)
	{
		printf("token.content=%s\n", (char *)token->content);
		token = token->next;
	}
	return (1);
}

void	ft_print_env_test(t_lst_env *lst_env)
{
	while (lst_env)
	{
		printf("key=%s, env=%s ", lst_env->key, lst_env->env);
		if (lst_env->val)
			printf("val=%s", lst_env->val);
		printf("\n");
		lst_env = lst_env->next;
	}
}
