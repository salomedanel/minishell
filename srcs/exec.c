/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:58:45 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/11 15:34:40 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

// void	exec_cmd(t_data *data)
// {

// }

void	launcher(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->ast[i] == T_BUILTIN)
			exec_builtin(data);
		// else if (data->ast[i] == T_CMD)
		// 	exec_cmd(data);
		// else if (data->ast[i] == T_WORD)
		// 	continue ;
		i++;
	}
}
