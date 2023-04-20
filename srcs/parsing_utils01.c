/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:49:26 by danelsalome       #+#    #+#             */
/*   Updated: 2023/04/20 17:43:36 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_squotes(char *arg, t_data *data, int index)
{
	int	i;
    int j;

	i = 0;
    j = 0;
	while (arg[i])
	{
		if (arg[i] != '\'')
        {
		    data->f_arg[index][j] = arg[i];
            j++;
        }
		i++;
    }
}

void	trim_dquotes(char *arg, t_data *data, int index)
{
	int	i;
    int j;

	i = 0;
    j = 0;
	while (arg[i])
	{
		if (arg[i] != '"')
        {
		    data->f_arg[index][j] = arg[i];
            j++;
        }
		i++;
    }
}

void    ft_strcpy(char *dest, char *src, int start)
{
    int i;
    
    i = 0;
    if (src == NULL)
        return ;
    while (src[start])
    {
        dest[i] = src[start];
        i++;
        start++;
    }
    return ;
}