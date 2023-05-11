/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:41:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/10 10:28:45 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("CTRL+C detected\n");
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("CTRL+D detected\n");
	exit(0);
}
