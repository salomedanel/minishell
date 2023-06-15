/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:41:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/13 12:13:58 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_ignore_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
	}
}

void	handle_sig_cmd(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		signal(SIGINT, ctrlc);
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("Quit (core dumped)\n");
		g_exit_code = 131;
	}
}

void	ctrlc(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sub_signal(t_data *data)
{
	int	j;

	j = -1;
	signal(SIGINT, handle_sig_cmd);
	signal(SIGQUIT, handle_sig_cmd);
	while (data->p_arg[++j])
		if (ft_strncmp(data->p_arg[j], "./", 2) == 0)
			ft_ignore_signal();
}
