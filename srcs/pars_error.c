/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/25 10:05:21 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	err_msg(char *err, char quote)
{
	int	i;

	i = 0;
	ft_printf("%s '%c'\n", err, quote);
	g_exit_code = 2;
	return ;
}

void	new_prompt()
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	syntax_err_utils(t_data *data, char c)
{
	err_msg(ERR_MSG, c);
	freefrom_syntax_err(data);
	new_prompt();
	return ;
}

void	syntax_error(t_data *data)
{
	sing_syntax_error(data);
	mult_syntax_error(data);
}

void	sing_syntax_error(t_data *data)
{
	int	i;
	int	j;
	int	count_mc;
	int	type;

	i = 0;
	while (data->f_arg[i])
	{
		j = 0;
		count_mc = 0;
		while (data->f_arg[i][j])
		{
			type = metachar_type(data->f_arg[i][j], &count_mc);
			if (type == 3 && j > 0)
				err_msg(ERR_MSG, '|');
			if (count_mc > 2)
				err_msg(ERR_MSG, data->f_arg[i][j]);
			j++;
		}
		i++;
	}
	return ;
}

void	mult_syntax_error(t_data *data)
{
	int	i;
	int	count_arg;
	int	contains_mc;

	i = 0;
	count_arg = tab_len(data->f_arg);
	while (data->f_arg[i])
	{
		contains_mc = str_contains_mc(data->f_arg[i]);
		if (i == count_arg - 1 && contains_mc > 0)
			err_msg(ERR_MSG, data->f_arg[i][0]);
		i++;
	}
	return ;
}
