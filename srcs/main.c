/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/30 00:33:40 by tmichel-         ###   ########.fr       */
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
	dup_env(&data, env);
	init_struct(&data);
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		if (prompt == NULL)
		{
			mini_exit_bis(&data);
			break ;
		}
		parsing(prompt, &data);
	}
	return (0);
}
