/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:17:16 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/24 16:02:54 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	init_ast(t_data *data)
{
	int	i;

	i = 0;
//	print_arg(data->tmp_arg);
	while (data->tmp_arg[i])
		i++;
	data->ast = malloc(sizeof(int) * (i));
	i = 0;
	while (data->tmp_arg[i])
	{
		data->ast[i] = -1;
		i++;
	}
	return (i);
}
