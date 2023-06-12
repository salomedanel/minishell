/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 23:34:56 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

void	init_struct(t_data *data)
{
	data->count_cmd = 0;
	data->count_prompts = 0;
	data->fd[0] = -1;
	data->fd[1] = -1;
}

t_data	*starton(void)
{
	static t_data	data = {0};

	return (&data);
}

int	main(int argc, char **argv, char **env)
{
	char			*prompt;
	t_data	*data;

	(void)argc;
	(void)argv;
	data = starton();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ctrlc);
	dup_env(data, env);
	init_struct(data);
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		if (prompt == NULL)
		{
			ft_putendl_fd("exit", 2);
			mini_exit_bis(data);
			break ;
		}
		parsing(prompt, data);
	}
	return (0);
}
