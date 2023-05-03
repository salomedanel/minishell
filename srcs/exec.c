/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:58:45 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/02 18:22:28 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	launcher(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->ast[i] == T_BUILTIN)
			exec_builtin(data);
		i++;
	}
}
