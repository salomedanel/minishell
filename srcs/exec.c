/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:58:45 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/25 16:34:18 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	launcher(char **envp, t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->ast[i] == T_BUILTIN)
			exec_builtin(envp, data);
		i++;
	}
}