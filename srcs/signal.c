/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:41:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/27 12:26:56 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	handle_sigint(int sig)
{
	(void)sig;
	g_exit_code = 130;
	ft_printf("^C\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}
