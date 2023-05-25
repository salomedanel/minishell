/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:15:19 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/25 13:49:18 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("arg[%d] = %s\n", i, arg[i]);
		i++;
	}
}

void	print_arg_ast(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		printf("farg[%d] = %s \t\t\t ast[%d] = %d\n", i, data->f_arg[i], i,
			data->ast[i]);
		i++;
	}
}
