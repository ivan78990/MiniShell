/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar_in_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduck <dduck@student.21-school.r>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:32:48 by dduck             #+#    #+#             */
/*   Updated: 2021/08/19 16:32:51 by dduck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dollar_ch1_quote(char **tmp, char **tmp2, char **tmp3, char **tmp4)
{
	*tmp4 = ft_strjoin(*tmp, *tmp2);
	ft_free_ptr(*tmp2);
	ft_free_ptr(*tmp);
	*tmp = ft_strjoin(*tmp4, *tmp3);
	ft_free_ptr(*tmp3);
	ft_free_ptr(*tmp4);
}

void	ft_dollar_get_tmp_in_qoute(char **tmp, t_count *cnt, int *i, char **str)
{
	char	*tmp_bef;
	char	*tmp_after;
	int		ln_tmp;
	int		ln_str;

	*i = cnt->j;
	ln_str = (int)ft_strlen(*str);
	ln_tmp = (int)ft_strlen(*tmp);
	tmp_bef = ft_substr(*str, 0, cnt->j);
	tmp_after = ft_substr(*str, cnt->j + ln_tmp + 1, ln_str - ln_tmp);
	ft_free_ptr(*tmp);
	*tmp = ft_strjoin(tmp_bef, tmp_after);
	ft_free_ptr(tmp_bef);
	ft_free_ptr(tmp_after);
}

char	*ft_dollar_in_quote(char *str, int *i, char **env)
{
	t_count	cnt;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	*i = ft_init_dollar(&cnt, i, str);
	if (*i == cnt.j)
		return (str);
	tmp = ft_substr(str, cnt.j + 1, *i - cnt.j - 1);
	cnt.k = -1;
	ft_check_env(env, &cnt, tmp);
	if (cnt.start)
	{
		ft_free_ptr(tmp);
		tmp2 = ft_substr(env[cnt.k], cnt.z + 1,
				ft_strlen(env[cnt.k]) - 1);
		tmp = ft_substr(str, 0, cnt.j);
		tmp3 = ft_strdup(str + *i);
		ft_dollar_ch1_quote(&tmp, &tmp2, &tmp3, &tmp4);
	}
	else
		ft_dollar_get_tmp_in_qoute(&tmp, &cnt, i, &str);
	ft_free_ptr(str);
	return (tmp);
}
