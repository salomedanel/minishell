/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/22 15:03:44 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	quote_err(t_data *data, char *err, char quote)
{
	int	i;

	i = 0;
	ft_printf("%s '%c'\n", err, quote);
	g_exit_code = 2;
	free(data->clean_prompt);
	while (data->new_env[i])
	{
		free(data->new_env[i]);
		free(data->prev_env[i]);
		i++;
	}
	free(data->new_env);
	free(data->prev_env);
	exit(0);
	return ;
}

// void	quote_err2(t_data *data, char *err, char quote)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("%s '%c'\n", err, quote);
// 	g_exit_code = 2;
// 	while (data->arg[i])
// 	{
// 		free(data->arg[i]);
// 		i++;
// 	}
// 	free(data->arg);
// 	return ;
// }

// void	metachar_err(t_data *data, char *err, char *metachar)
// {
// 	int	i;

// 	i = 0;
// 	ft_printf("%s '%s'\n", err, metachar);
// 	g_exit_code = 2;
// 	while (data->f_arg[i])
// 	{
// 		free(data->f_arg[i]);
// 		i++;
// 	}
// 	free(data->f_arg);
// 	free(data->ast);
// 	return ;
// }
