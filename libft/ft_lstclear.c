/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 13:25:48 by warchang          #+#    #+#             */
/*   Updated: 2020/11/20 14:08:34 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*one;
	t_list	*tmp;

	if (!del)
		return ;
	one = *lst;
	while (one)
	{
		tmp = one->next;
		ft_lstdelone(one, del);
		one = tmp;
	}
	*lst = NULL;
}
