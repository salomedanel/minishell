/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:13:22 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/15 17:11:38 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	char	t;
	size_t	count;
	char	*trimmed;

	i = 0;
	t = c;
	count = 0;
	trimmed = ft_strtrim(s, &t);
	if (!trimmed)
		return (0);
	while (*(trimmed + i))
	{
		count++;
		while (*(trimmed + i) && *(trimmed + i) != c)
			i++;
		while (*(trimmed + i) && *(trimmed + i) == c)
			i++;
		if (!*(trimmed + i))
			break ;
	}
	free (trimmed);
	return (count);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	**tab;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	while (j < ft_count_words(s, c))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		k = i;
		while (*(s + i) && *(s + i) != c)
			i++;
		*(tab + j++) = ft_substr(s, k, i - k);
	}
	*(tab + j) = NULL;
	return (tab);
}
