/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:20:08 by dduck             #+#    #+#             */
/*   Updated: 2021/08/12 15:20:09 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_and_free(char *str, char *tmp2, char *tmp3)
{
	char	*str_ret;

	str_ret = ft_strjoin(str, tmp3);
	ft_free_ptr(str);
	ft_free_ptr(tmp2);
	ft_free_ptr(tmp3);
	return (str_ret);
}

char	*ft_dquot(char *str, int *i, char **env, int *flag_quote)
{
	int		j;
	char	*tmp_bef;
	char	*tmp_core;
	char	*tmp_aft;

	j = *i;
	*flag_quote = 1;
	while (str[++(*i)])
	{
		if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$'
				|| str[*i + 1] == '\\'))
			str = ft_slash(str, i);
		if (str[*i] == '$')
			str = ft_dollar_in_quote(str, i, env);
		if (str[*i] == '\"')
			break ;
	}
	tmp_bef = ft_substr(str, 0, j);
	tmp_core = ft_substr(str, j + 1, *i - j - 1);
	tmp_aft = ft_strdup(str + *i + 1);
	ft_free_ptr(str);
	str = ft_strjoin(tmp_bef, tmp_core);
	ft_free_ptr(tmp_bef);
	tmp_bef = ft_strjoin_and_free(str, tmp_core, tmp_aft);
	return (tmp_bef);
}
