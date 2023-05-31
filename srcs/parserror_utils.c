/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserror_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:39:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/31 11:31:59 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	metachar_type(char c)
{
	if (c == '>')
		return (1);
	if (c == '<')
		return (2);
	if (c == '|')
		return (3);
	return (0);
}

int	count_metac(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (is_metachar(str[i]) > 0)
			count++;
		i++;
	}
	return (count);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	minicd_err(void)
{
	ft_putstr_fd("cd: too many arguments\n", 2);
	g_exit_code = 1;
	return (g_exit_code);
}

int	contain_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}
