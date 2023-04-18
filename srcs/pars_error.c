/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/18 11:11:53 by sdanel           ###   ########.fr       */
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
	g_exit_code = 3;
	while (data->arg[i])
	{
		free(data->arg[i]);
		i++;
	}
	free(data->arg);
	return ;
}
