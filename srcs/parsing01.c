/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:18:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/12 16:40:13 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	odd_dquotes(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->new_prompt[i])
	{
		if (data->new_prompt[i] == '"')
			count++;
		i++;
	}
	if (count % 2 == 0 && odd_squotes(data) )
		return (0);
	else
		return (1);
}

int	odd_squotes(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->new_prompt[i])
	{
		if (data->new_prompt[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

void	space_dquotes(t_data *data)
{
	int	i;
	
	i = 0;
	while (data->new_prompt[i])
	{
		if (data->new_prompt[i] == '"')
		{
			while (data->new_prompt[i] != '"')
			{
				if (data->new_prompt[i] == 32)
					data->new_prompt[i] = 90;
			}
		}
		i++;
	}


}

