/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserror_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 17:39:25 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/30 08:43:59 by sdanel           ###   ########.fr       */
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

int	syntaxerr_utils(t_data *data, int i, int count_arg, int type)
{
	if (count_arg == 1 && count_metac(data->f_arg[i]) > 0 && type == 3)
	{
		err_msg_char(ERR_MSG, '|');
		return (0);
	}
	if (count_arg > 1 && count_metac(data->f_arg[i]) == 1
		&& count_metac(data->f_arg[i + 1]) == 1 && metachar_type(data->f_arg[i + 1][0]) == 3)
	{
		err_msg_char(ERR_MSG, '|');
		return (0);
	}
	if (count_arg > 1 && count_metac(data->f_arg[i]) == 1
		&& count_metac(data->f_arg[i + 1]) == 1)
	{
		err_msg_newline(ERR_MSG_NL);
		return (0);
	}
	if (count_arg > 1 && count_metac(data->f_arg[i]) >= 2
		&& (metachar_type(data->f_arg[i + 1][0]) != 1
			|| metachar_type(data->f_arg[i + 1][0] != 2)))
	{
		err_msg_char(ERR_MSG, data->f_arg[i][0]);
		return (0);
	}
	if (count_arg > 1 && count_metac(data->f_arg[i]) > 0
		&& i == count_arg - 1 && metachar_type(data->f_arg[i][0]) != 3)
	{
		err_msg_newline(ERR_MSG_NL);
		return (0);
	}
	return (1);
}

int	minicd_err(void)
{
	ft_putstr_fd("cd: too many arguments\n", 2);
	g_exit_code = 1;
	return (g_exit_code);
}
