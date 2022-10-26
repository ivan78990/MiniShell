/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_redir_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:20:55 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:20:59 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_its_redir(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "<"))
		return (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	return (0);
}

t_redir	*ft_init_struct_redir(void)
{
	t_redir	*tmp_redir;

	tmp_redir = NULL;
	tmp_redir = ft_calloc(1, sizeof (t_redir));
	if (!tmp_redir)
		exit(EXIT_FAILURE);
	tmp_redir->filename = NULL;
	tmp_redir->type_redir = 0;
	tmp_redir->num_redir = -1;
	return (tmp_redir);
}

void	ft_get_number_lst_redir(t_list *lst_redir)
{
	int		i;
	t_redir	*strct_redir;

	strct_redir = NULL;
	i = 0;
	while (lst_redir)
	{
		strct_redir = lst_redir->content;
		strct_redir->num_redir = i;
		lst_redir = lst_redir->next;
		i++;
	}
}

t_list	*ft_get_list_redirect(t_list *token, t_count *cnt)
{
	t_list	*new_list_redirect;
	t_redir	*new_struct_redirect;

	new_list_redirect = NULL;
	while (token)
	{
		new_struct_redirect = ft_init_struct_redir();
		new_struct_redirect->type_redir = ft_its_redir((char *)token->content);
		token = token->next;
		cnt->count_drop_token_redir++;
		new_struct_redirect->filename = ft_strdup(token->content);
		token = token->next;
		cnt->count_drop_token_redir++;
		ft_lstadd_back(&new_list_redirect, ft_lstnew(new_struct_redirect));
		if (token)
		{
			if ((!ft_strcmp((char *) token->content, "|" ))
				|| (!ft_its_redir((char *) token->content)))
			{
				cnt->count_drop_token_redir -= 1;
				return (new_list_redirect);
			}
		}
	}
	return (new_list_redirect);
}

void	ft_get_flag_redir(int *flag_redir_read, int *flag_redir_write,
						  t_list *lst_redir)
{
	t_redir	*strct_redir;

	while (lst_redir)
	{
		strct_redir = lst_redir->content;
		if (strct_redir->type_redir == 1 || strct_redir->type_redir == 2)
			*flag_redir_write = 1;
		if (strct_redir->type_redir == 3 || strct_redir->type_redir == 4)
			*flag_redir_read = 1;
		lst_redir = lst_redir->next;
	}
}
