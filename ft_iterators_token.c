/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterators_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:19:06 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:19:07 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_iterator_dquote(const char *str, t_count *tc)
{
	while (str[++tc->i] != '\"' && tc->i <= tc->len)
		tc->j++;
}

void	ft_iterator_nonspec(const char *str, t_count *tc)
{
	int	flag_quote;

	flag_quote = 0;
	while (tc->i <= tc->len && (!ft_isspace(str[tc->i]) || flag_quote)
		&& !ft_check_sym(str[tc->i], 1))
	{
		if (str[tc->i] == '\"' || str[tc->i] == '\'')
			flag_quote = 1;
		tc->i++;
		tc->j++;
	}
	tc->i -= 1;
}

void	ft_iterator_pipe(const char *str, t_count *tc)
{
	while (tc->i <= tc->len && (ft_check_sym(str[tc->i], 1) == 2))
	{
		tc->i++;
		tc->j++;
	}
	tc->i -= 1;
}

void	ft_iterator_redir(const char *str, t_count *tc)
{
	while (tc->i <= tc->len && (ft_check_sym(str[tc->i], 1) == 1))
	{
		tc->i++;
		tc->j++;
	}
	tc->i -= 1;
}

// Проверка на кавычки для формирования единого токена
void	ft_check_tokensym(char *str, t_count *tc)
{
	if (ft_strchr(QUOTE_SYM, str[tc->i]))
	{
		while (str[tc->i])
		{
			if (str[tc->i] == '\'')
			{
				while (str[++tc->i] != '\'' && tc->i <= tc->len)
					tc->j++;
			}
			else if (str[tc->i] == '\"')
				ft_iterator_dquote(str, tc);
			if (!str[tc->i + 1] || !ft_strchr(QUOTE_SYM, str[tc->i + 1]))
				break ;
			tc->i++;
			tc->j += 2;
		}
		tc->j += 2;
	}
	else if (!ft_check_sym(str[tc->i], 1))
		ft_iterator_nonspec(str, tc);
	else if (str[tc->i] == '|')
		ft_iterator_pipe(str, tc);
	else if ((ft_check_sym(str[tc->i], 1) == 1))
		ft_iterator_redir(str, tc);
	tc->k = tc->i;
}
