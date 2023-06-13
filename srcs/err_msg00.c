/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 11:15:39 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/13 10:57:28 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	err_export_opt(t_data *data, int i)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putchar_fd(data->cmd_tab[i][0], 2);
	ft_putchar_fd(data->cmd_tab[i][1], 2);
	ft_putstr_fd("': invalid option\n", 2);
	g_exit_code = 2;
}

void	err_export_id(t_data *data, int i)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(data->cmd_tab[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_exit_code = 1;
}

void	err_msg_char(char *err, char quote, t_data *data, int i)
{
	ft_putstr_fd(err, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd(quote, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
	g_exit_code = 2;
	if (i != 0)
		freetab(data->f_arg);
	return ;
}

void	err_msg_str(char *err, char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(err, 2);
	return ;
}

void	err_msg_newline(char *err, t_data *data)
{
	ft_putendl_fd(err, 2);
	g_exit_code = 2;
	freetab(data->f_arg);
	return ;
}
