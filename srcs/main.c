/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/26 13:06:50 by sdanel           ###   ########.fr       */
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
	dup_env(&data, env);
	data.path = NULL;
	data.ast = NULL;
	data.tmp_arg = NULL;
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
