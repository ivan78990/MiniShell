/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoincl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 11:00:36 by warchang          #+#    #+#             */
/*   Updated: 2021/08/18 11:00:37 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoincl(char *s1, char *s2, int free_both)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (!new)
		return (NULL);
	free(s1);
	s1 = NULL;
	if (free_both)
	{
		free(s2);
		s2 = NULL;
	}
	return (new);
}
