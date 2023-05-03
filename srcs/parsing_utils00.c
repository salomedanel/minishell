/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:04:45 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/03 14:18:53 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	if (c == 32)
		return (2);
	return (0);
}

int	cpy_prompt(char *prompt, char *new_prompt, int j, int i)
{
	new_prompt[j] = prompt[i];
	new_prompt[++j] = 32;
	return (j);
}

int	open_quotes(char c, int *dq_open, int *sq_open, int *count)
{
	if (c == '"' && *dq_open == 0 && *sq_open == 0)
	{
		*dq_open = 1;
		*count = *count - 1;
	}
	if (c == '\'' && *dq_open == 0 && *sq_open == 0)
	{
		*sq_open = 1;
		*count = *count - 1;
	}
	return (*count);
}

int	close_quotes(char c, int *dq_open, int *sq_open, int *count)
{
	if (c == '"' && *dq_open == 1)
	{
		*dq_open = 0;
		*count = *count - 1;
	}
	if (c == '\'' && *sq_open == 1)
	{
		*sq_open = 0;
		*count = *count - 1;
	}
	return (*count);
}

void	print_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		printf("arg[%d] = %s\n", i, arg[i]);
		i++;
	}
}
