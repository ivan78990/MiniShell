/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:09:08 by warchang          #+#    #+#             */
/*   Updated: 2020/11/18 17:07:11 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_count(char const *s1, char c)
{
	size_t	i;
	size_t	str;

	i = 0;
	str = 0;
	while (s1[i] != '\0')
	{
		if (str == 0 && s1[i] != c)
			str++;
		if (s1[i] == c && s1[i + 1] != c && s1[i + 1] != '\0')
		{
			str++;
		}
		i++;
	}
	return (str);
}

static void	ft_free(char **matrix, size_t num)
{
	if (num == 0)
		free(matrix);
	else
	{
		while ((num - 1) > 0)
		{
			free(matrix[num - 1]);
			num--;
		}
		free(matrix);
	}
}

static	void	ft_creat_words(const char *s, char c, int i, char **matrix)
{
	size_t		index;
	int			len;
	int			start;

	index = 0;
	start = 0;
	while (index < ft_count(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (i == 0 || ((s[i] != c) && (s[i - 1] == c || s[i - 1] == '\0')))
			start = i;
		if (s[i + 1] == c || s[i + 1] == '\0')
		{
			len = i - start + 1;
			matrix[index++] = ft_substr(s, i - len + 1, len);
			if (!matrix[index - 1])
			{
				ft_free(matrix, index - 1);
				return ;
			}
		}
		i++;
	}
	matrix[index] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**matrix_new;
	int		num_words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	num_words = ft_count(s, c);
	matrix_new = (char **)malloc((num_words + 1) * sizeof(char *));
	if (!matrix_new)
		return (NULL);
	ft_creat_words(s, c, i, matrix_new);
	return (matrix_new);
}
