/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:18:43 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/22 16:19:56 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

// void	child(t_data *data)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	pid = fork();
// 	if (!pid)
// 	{
// 		if (data->prev_pipe == -1 && data->cmd_id < data->cmd_count - 1)
// 		{
// 			dupnclose(data, data->in, STDIN_FILENO);
// 			dupnclose(data, fd[1], STDOUT_FILENO);
// 			data->prev_pipe = fd[0];
// 		}
// 		else

// 		// exec_builtin(data->f_arg[i]);
// 	}
// }