/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 15:11:47 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/23 16:12:25 by sdanel           ###   ########.fr       */
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
	while (src[i])
	{
		if (src[i] == ' ' && (i == 0 || i == len) && src[i])
			i++;
		dest[j] = src[i];
		j++;
		i++;
	}
	if (i < count)
		dest[j - 1] = '\0';
	dest[j] = '\0';
	return ;
}

char	**split_pipe(t_data *data)
{
	char	*str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	data->count_cmd = count_cmd(data);
	str = ft_jointab(data->f_arg);
	data->tmp_arg = ft_split(str, '|');
	while (data->tmp_arg[count])
		count++;
	data->p_arg = malloc(sizeof(char *) * (count + 1));
	while (data->tmp_arg[i])
	{
		data->p_arg[i] = malloc(sizeof(char) * (ft_strlen(data->tmp_arg[i])
					+ 1));
		if (data->p_arg[i] == NULL)
			return (NULL);
		ft_strcpy_pipe(data->p_arg[i], data->tmp_arg[i], count);
		i++;
	}
	data->p_arg[i] = NULL;
	printf("PIPE ARG\n");
	print_arg(data->p_arg);
	free(str);
	free_tmp(data);
	return (data->p_arg);
}