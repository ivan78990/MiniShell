/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:20:18 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:20:20 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_slash(char *str, int *i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, *i);
	tmp2 = ft_strdup(str + *i + 1);
	tmp3 = ft_strjoin(tmp, tmp2);
	free(str);
	free(tmp2);
	free(tmp);
	++(*i);
	return (tmp3);
}

char	*ft_quot(char *str, int *i, int *flag_quote)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	j = *i;
	*flag_quote = 1;
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
			break ;
	}
	tmp = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strdup(str + *i + 1);
	tmp4 = ft_strjoin(tmp, tmp2);
	ft_free_ptr(tmp);
	tmp = ft_strjoin(tmp4, tmp3);
	ft_free_ptr(tmp2);
	ft_free_ptr(tmp3);
	ft_free_ptr(tmp4);
	ft_free_ptr(str);
	(*i)++;
	return (tmp);
}

char	*ft_parse_processor(char *str, char **env, int *flag_qoute)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(str);
	i = -1;
	while (tmp[++i])
	{
		if (tmp[i] == '\'')
		{
			tmp = ft_quot(tmp, &i, flag_qoute);
			i -= 2;
		}
		if (tmp[i] == '\"')
		{
			tmp = ft_dquot(tmp, &i, env, flag_qoute);
			i -= 2;
		}
		if (tmp[i] == '\\')
			tmp = ft_slash(tmp, &i);
		if (tmp[i] == '$')
			tmp = ft_dollar(tmp, &i, env);
	}
	return (tmp);
}

void	ft_get_flag_after_redir(t_list *lst_comm)
{
	t_comm	*tmp;
	t_comm	*tmp2;

	while (lst_comm)
	{
		tmp = lst_comm->content;
		lst_comm = lst_comm->next;
		if (lst_comm)
		{
			tmp2 = lst_comm->content;
			if (tmp->lst_redir)
			{
				tmp2->flag_after_redir = 1;
			}
		}
	}
}

t_list	*ft_parser(t_data *data, t_list *lst_token)
{
	t_list	*lst_comm;

	lst_comm = NULL;
	if (ft_get_counttoken(lst_token))
		lst_comm = ft_get_list_comm(data, lst_token);
	ft_get_flag_after_redir(lst_comm);
	return (lst_comm);
}
