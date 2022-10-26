/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchcl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 11:00:20 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 11:00:21 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoinchcl(char *s1, char c)
{
	char	*new;

	new = ft_strjoinch(s1, c);
	if (!new)
		return (NULL);
	free(s1);
	s1 = NULL;
	return (new);
}
