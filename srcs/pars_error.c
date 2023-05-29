/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 15:01:46 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	err_msg_char(char *err, char quote)
{
	ft_printf("%s '%c'\n", err, quote);
	g_exit_code = 2;
	return ;
}

void	err_msg_newline(char *err)
{
	ft_printf("%s\n", err);
	g_exit_code = 2;
	return ;
}

int	syntax_error(t_data *data)
{
	if (err_onlyspace(data) == 0)
		return (0);
	if (sing_syntax_error(data) == 0)
		return (0);
	if (mult_syntax_error(data) == 0)
		return (0);
	return (1);
}

int	sing_syntax_error(t_data *data)
{
	int	i;
	int	j;
	int	count_mc;
	int	type;

	i = 0;
	count_mc = count_metac(data->f_arg[i]);
	while (data->f_arg[i])
	{
		j = 0;
		while (data->f_arg[i][j])
		{
			type = metachar_type(data->f_arg[i][j]);
			if ((type == 3 && j > 0) || (type == 3 && ft_strlen(data->f_arg[i]) == 1 && i == 0))
			{
				err_msg_char(ERR_MSG, '|');
				return (0);
			}
			if (count_mc == 2)
			{
				err_msg_newline(ERR_MSG_NL);
				return (0);
			}
			if (count_mc > 2)
			{
				err_msg_char(ERR_MSG, data->f_arg[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	mult_syntax_error(t_data *data)
{
	int	i;
	int	count_arg;
	int	contains_mc;

	i = 0;
	count_arg = tab_len(data->f_arg);
	while (data->f_arg[i])
	{
		contains_mc = str_contains_mc(data->f_arg[i]);
		if (i == count_arg - 1 && contains_mc <= 2 && contains_mc > 0)
		{
			err_msg_newline(ERR_MSG_NL);
			return (0);
		}
		if (i == count_arg - 1 && contains_mc > 2)
		{
			err_msg_char(ERR_MSG, data->f_arg[i][0]);
			return (0);
		}
		i++;
	}
	return (1);
}
