/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 11:06:49 by dduck             #+#    #+#             */
/*   Updated: 2021/07/29 11:06:53 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_quote(const char *token)
{
	int	i;
	int	flag_dquote;
	int	flag_quote;

	i = -1;
	if (!token)
		return (0);
	flag_quote = 0;
	flag_dquote = 0;
	while (token[++i])
	{
		if (token[i] == '\'')
			flag_quote++;
		if (token[i] == '\"')
			flag_dquote++;
	}
	if (flag_quote % 2 != 0 || flag_dquote % 2 != 0)
		return (0);
	return (1);
}

int	ft_check_token_aft_bef(char *bef, char *aft)
{
	if (ft_its_redir(bef) && ft_its_redir(aft))
		return (0);
	if (ft_its_redir(bef) && !ft_strcmp(aft, "|"))
		return (0);
	return (1);
}

int	ft_check_token_syntax(t_list *lst_token)
{
	char	*bef_token;
	char	*after_token;

	while (lst_token)
	{
		bef_token = lst_token->content;
		if (!ft_check_quote(bef_token))
			return (0);
		lst_token = lst_token->next;
		if (lst_token)
			after_token = lst_token->content;
		if (!ft_check_token_aft_bef(bef_token, after_token))
			return (0);
	}
	return (1);
}
