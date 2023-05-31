/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:11:47 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 15:37:33 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy_pipe(char *dest, char *src, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(src);
	(void)count;
	while (src && src[i])
	{
		if (src[i] == ' ' && (i == 0 || i == len) && src[i])
			i++;
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return ;
}

char	**split_pipe(t_data *data, int i, int j)
{
	int		count;

	count = 0;
	data->count_cmd = count_cmd(data);
	data->str = ft_jointab(data->f_arg, i, j);
	data->tmp_arg = ft_split(data->str, '|');
	while (data->tmp_arg[count])
		count++;
	data->p_arg = malloc(sizeof(char *) * (count + 1));
	if (data->p_arg == NULL)
		return (NULL);
	dup_tab(data->tmp_arg, data->p_arg);
	freetab(data->tmp_arg);
	return (data->p_arg);
}
