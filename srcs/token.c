/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:33:40 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/22 16:21:42 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token(t_data *data)
{
	int	nb_arg;

	nb_arg = init_ast(data);
	if (token_metachar(data) == -1)
		return ;
	if (token_word_metachar(data, nb_arg) == -1)
		return ;
	if (token_command_option(data) == -1)
		return ;
	//print_arg_ast(data);
}

int	token_metachar(t_data *data)
{
	int	i;

	i = -1;
	while (data->f_arg[++i])
	{
		if (!ft_strcmp(data->f_arg[i], "|"))
			data->ast[i] = T_PIPE;
		else if (!ft_strcmp(data->f_arg[i], ">"))
			data->ast[i] = T_REDOUT;
		else if (!ft_strcmp(data->f_arg[i], "<"))
			data->ast[i] = T_REDIN;
		else if (!ft_strcmp(data->f_arg[i], "<<"))
			data->ast[i] = T_HERE_DOC;
		else if (!ft_strcmp(data->f_arg[i], ">>"))
			data->ast[i] = T_RED_OUT_APPEND;
	}
	return (0);
}

int	token_word_metachar(t_data *data, int nb_arg)
{
	int	i;

	i = -1;
	(void)nb_arg;
	while (data->f_arg[++i])
	{
		if (!ft_strcmp(data->f_arg[i], ">") && data->ast[i + 1])
			data->ast[i + 1] = T_OUTFILE_TRUNC;
		else if (!ft_strcmp(data->f_arg[i], "<") && data->ast[i + 1])
			data->ast[i + 1] = T_INFILE;
		else if (!ft_strcmp(data->f_arg[i], "<<") && data->ast[i + 1])
			data->ast[i + 1] = T_LIMITER;
		else if (!ft_strcmp(data->f_arg[i], ">>") && data->ast[i + 1])
			data->ast[i + 1] = T_OUTFILE_APPEND;
	}
	return (0);
}

int	token_command_option(t_data *data)
{
	int	i;

	i = -1;
	while (data->f_arg[++i])
		if (data->ast[i] == -1)
			data->ast[i] = T_CMD;
	// token_command_builtin(data);
	return (0);
}

// int	token_command_builtin(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (data->f_arg[i])
// 	{
// 		if (data->ast[i] == 9 && is_builtin(data->f_arg[i]) == 1)
// 			data->ast[i] = T_BUILTIN;
// 		i++;
// 	}
// 	return (0);
// }
