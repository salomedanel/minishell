/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:04:45 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/18 11:44:56 by sdanel           ###   ########.fr       */
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

int	count_dquotes(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == 34)
			count++;
		i++;
	}
	return (count);
}

int	count_squotes(char *arg)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == 39)
			count++;
		i++;
	}
	return (count);
}

void	print_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		ft_printf("arg[%d] = %s\n", i, arg[i]);
		i++;
	}
}
