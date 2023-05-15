/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/15 15:38:39 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	t_data	data;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_sigint);
	//signal(SIGINT, handle_sigquit);
	dup_env(&data, env);
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		split_input(prompt, &data);
		if (prompt == NULL)
		{
			mini_exit(&data);
			break ;
		}
		free_dobby(&data);
	}
	return (0);
}
