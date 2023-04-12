/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:36:03 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/12 14:14:32 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		prompt = readline("minishell> ");
		add_history(prompt);
		split_input(prompt);
		if (prompt == NULL)
			break ;
	}
	return (0);
}
