/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/08 17:13:37 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	syntax_err(t_data *data, t_quotes *quotes)
{
	int	i;
	int	count_arg;
	int	type;

	i = -1;
	count_arg = tab_len(data->f_arg);
	while (data->f_arg[++i])
	{
		type = metachar_type(data->f_arg[i][0]);
		if (count_arg == 1 && count_metac(data->f_arg[i]) < 3
			&& count_metac(data->f_arg[i]) > 0 && type != 3)
		{
			err_msg_newline(ERR_MSG_NL, data);
			return (0);
		}
		if (count_arg == 1 && count_metac(data->f_arg[i]) > 2 && type != 3)
		{
			err_msg_char(ERR_MSG, data->f_arg[i][0], data, 1);
			return (0);
		}
		if (syntaxerr_utils00(data, i, count_arg, type) == 0
			|| syntaxerr_utils01(data, i, count_arg, quotes) == 0)
			return (0);
	}
	return (1);
}

int	syntaxerr_utils00(t_data *data, int i, int count_arg, int type)
{
	if (count_arg == 1 && count_metac(data->f_arg[i]) > 0 && type == 3)
	{
		err_msg_char(ERR_MSG, '|', data, 1);
		return (0);
	}
	if (metachar_type(data->f_arg[i][0]) == 3 && (i == count_arg - 1 || i == 0))
	{
		err_msg_char(ERR_MSG, '|', data, 1);
		return (0);
	}
	if (count_arg > 1 && count_metac(data->f_arg[i]) == 1
		&& count_metac(data->f_arg[i + 1]) == 1 && type != 3)
	{
		err_msg_char(ERR_MSG, data->f_arg[i][0], data, 1);
		return (0);
	}
	return (1);
}

int	syntaxerr_utils01(t_data *data, int i, int count_arg, t_quotes *quotes)
{
	if (count_arg > 1 && count_metac(data->f_arg[i]) > 2)
	{
		err_msg_char(ERR_MSG, data->f_arg[i][0], data, 1);
		return (0);
	}
	if (count_arg > 1 && count_metac(data->f_arg[i]) > 0 && i == count_arg - 1
		&& metachar_type(data->f_arg[i][0]) != 3 && quotes->dq_open == 0
		&& quotes->sq_open == 0)
	{
		err_msg_char(ERR_MSG, data->f_arg[i][0], data, 1);
		return (0);
	}
	return (1);
}

int	err_special(t_data *data)
{
	int	i;

	i = -1;
	while (data->clean_prompt[++i] == 32)
	{
		if (i == (ft_strlen(data->clean_prompt) - 1))
		{
			free(data->clean_prompt);
			return (0);
		}
	}
	return (1);
}
