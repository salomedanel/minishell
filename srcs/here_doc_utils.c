/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:45:57 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/13 09:45:06 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_here_docs(t_data *data)
{
	int		count;
	char	*str;

	str = data->str;
	count = 0;
	while (1)
	{
		str = ft_strnstr(str, "<<", ft_strlen(str));
		if (str)
			count++;
		else
			break ;
		str += 2;
	}
	return (count);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|", str[i]))
	{
		i++;
		r++;
	}
	return (r);
}

char	*get_word(char *str)
{
	int		i;
	int		r;
	char	*new;

	new = malloc(get_len_word(str) + 1);
	i = 0;
	r = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("><|", str[i]))
		new[r++] = str[i++];
	new[r] = '\0';
	return (new);
}

void	close_fd(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_here)
		close(data->here[i].fd[0]);
}