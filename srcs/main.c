/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/19 18:53:40 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

int	main(int argc, char **argv, char **env)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		split_input(prompt, env);
		if (prompt == NULL)
			break ;
	}
	return (0);
}

