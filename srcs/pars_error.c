/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/02 16:23:55 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	quote_err(t_data *data, char *err, char quote)
{
	ft_printf("%s '%c'\n", err, quote);
	g_exit_code = 2;
	free(data->clean_prompt);
	return ;
}

void	quote_err2(t_data *data, char *err, char quote)
{
	int	i;

	i = 0;
	ft_printf("%s '%c'\n", err, quote);
	g_exit_code = 2;
	while (data->arg[i])
	{
		free(data->arg[i]);
		i++;
	}
	free(data->arg);
	return ;
}

void	metachar_err(t_data *data, char *err, char *metachar)
{
	int	i;

	i = 0;
	ft_printf("%s '%s'\n", err, metachar);
	g_exit_code = 2;
	while (data->f_arg[i])
	{
		free(data->f_arg[i]);
		i++;
	}
	free(data->f_arg);
	free(data->ast);
	return ;
}
