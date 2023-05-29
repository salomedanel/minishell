/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 20:16:30 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	err_msg_char(char *err, char quote)
{
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
	g_exit_code = 2;
	return ;
}

void	err_msg_str(char *err, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(err, 2);
	return ;
}

void	err_msg_newline(char *err)
{
	ft_putendl_fd(err, 2);
	g_exit_code = 2;
	return ;
}

int	syntax_err(t_data *data)
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
			err_msg_newline(ERR_MSG_NL);
			return (0);
		}
		if (count_arg == 1 && count_metac(data->f_arg[i]) > 2 && type != 3)
		{
			printf("here\n");
			err_msg_char(ERR_MSG, data->f_arg[i][0]);
			return (0);
		}
		if (syntaxerr_utils(data, i, count_arg, type) == 0)
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
			return (0);
	}
	i = -1;
	while (data->clean_prompt[++i])
	{
		if (data->clean_prompt[i] == '/')
		{
			err_msg_str(ERR_MSG_NODIR, data->clean_prompt);
			g_exit_code = 126;
			return (0);
		}
	}
	return (1);
}
