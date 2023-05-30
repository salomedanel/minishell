/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 00:22:20 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

void	init_struct(t_data *data)
{
	data->path = ft_get_path(data);
	data->count_cmd = 0;
	data->fd[0] = -1;
	data->fd[1] = -1;
}

int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	static t_data	data = {0};

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handle_heredoc);
	dup_env(&data, env);
	init_struct(&data);
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		if (prompt == NULL)
		{
			ft_putendl_fd("exit", 2);
			mini_exit_bis(&data);
			break ;
		}
		parsing(prompt, &data);
		if (data.p_arg)
			freetab(data.p_arg);
		if (data.f_arg)
			freetab(data.f_arg);
	}
	return (0);
}
