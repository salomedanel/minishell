/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/27 08:34:24 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

void	init_struct(t_data *data)
{
	data->ast = NULL;
	data->tmp_arg = NULL;
	data->in = dup(STDIN_FILENO);
	data->out = dup(STDOUT_FILENO);
	data->prev_pipe = -1;
	data->act_fd = -1;
	data->path = ft_get_path(data);
}

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	t_data	data;

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
		// if (g_exit_code > 2)
		// {
		// 	printf("exit_code = %d\n", g_exit_code);
		// 	free_dobby(&data);
		// }
	}
	return (0);
}
