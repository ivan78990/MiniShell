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

int	ft_check_sym(char sym, int flag)
{
	if (!flag)
	{
		if (sym == '|')
			return (1);
	}
	if (flag == 1)
	{
		if (sym == '>' || sym == '<')
			return (1);
		if (sym == '|' )
			return (2);
	}
	return (0);
}

int	ft_check_comb(char a, char b, char c)
{
	if (ft_check_sym(a, 1) && ft_check_sym(b, 1)
		&& ft_check_sym(c, 1))
		return (1);
	if ((a == '|' && b == '|') || (b == '|' && c == '|'))
		return (1);
	return (0);
}

void	ft_iter_drop_quote_for_syntax(int *i, char *str)
{
	if (str[*i] == '\"')
	{
		while (str[++(*i)] != '\"')
			;
	}
	if (str[*i] == '\'')
	{
		while (str[++(*i)] != '\'')
			;
	}
}

int	ft_check_syntax_redir(char *str, int len)
{
	int		i;
	char	a;
	char	b;
	char	c;

	i = -1;
	while (str[++i] && i + 1 < len)
	{
		ft_iter_drop_quote_for_syntax(&i, str);
		if (((str[i] == '<') && (str[i + 1] == '>'))
			|| ((str[i] == '>') && (str[i + 1] == '<')))
			return (1);
		if ((i + 2) < len)
		{
			a = str[i];
			b = str[i + 1];
			c = str[i + 2];
		}
		if (ft_check_comb(a, b, c))
			return (1);
	}
	return (0);
}

int	ft_check_syntax(char *str, int str_len)
{
	int		i;
	int		len;

	i = 0;
	len = str_len - 1;
	while (ft_isspace(str[i]) && i < len)
		i++;
	if (ft_check_sym(str[i], 0))
		return (1);
	while (ft_isspace(str[len]))
		len--;
	if (ft_check_sym(str[len], 1))
		return (1);
	if (ft_strchr(&str[len], '\\'))
		return (1);
	i = -1;
	if (ft_check_syntax_redir(str, len))
		return (1);
	return (0);
}
