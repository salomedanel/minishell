/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:33:40 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/15 12:28:02 by tmichel-         ###   ########.fr       */
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
}

int	token_metachar(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->f_arg[i][0] == '|')
			data->ast[i] = T_PIPE;
		if (data->f_arg[i][0] == '>')
			data->ast[i] = T_REDOUT;
		if (data->f_arg[i][0] == '<')
			data->ast[i] = T_REDIN;
		if (data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<')
			data->ast[i] = T_HERE_DOC;
		if (data->f_arg[i][0] == '>' && data->f_arg[i][1] == '>')
			data->ast[i] = T_RED_OUT_APPEND;
		i++;
	}
	return (0);
}

int	token_word_metachar(t_data *data, int nb_arg)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (i < nb_arg && data->f_arg[i][0] == '>' && data->ast[i] != 1
			&& data->ast[i] != 4)
			data->ast[i + 1] = T_OUTFILE_TRUNC;
		if (i != 0 && data->f_arg[i - 1] && data->f_arg[i][0] == '<'
			&& data->ast[i] != 2)
			data->ast[i - 1] = T_INFILE;
		if (i < nb_arg && data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<'
			&& data->ast[i] != 3)
			data->ast[i + 1] = T_LIMITER;
		if (i != 0 && data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<')
			data->ast[i - 1] = T_CMD;
		if (i < nb_arg && data->f_arg[i][0] == '>' && data->f_arg[i][1] == '>'
			&& data->ast[i] != 4)
			data->ast[i + 1] = T_OUTFILE_APPEND;
		i++;
	}
	return (0);
}

int	token_command_option(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->ast[i] == -1 && i == 0)
			data->ast[i] = T_CMD;
		if (data->ast[i] == -1 && data->ast[i - 1] == 0)
			data->ast[i] = T_CMD;
		if (data->ast[i] == -1 && data->f_arg[i][0] == '-')
			data->ast[i] = T_OPTION;
		else if (data->ast[i] == -1)
			data->ast[i] = T_WORD;
		i++;
	}
	token_command_builtin(data);
	return (0);
}

int	token_command_builtin(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->ast[i] == 9 && is_builtin(data->f_arg[i]) == 1)
			data->ast[i] = T_BUILTIN;
		i++;
	}
	return (0);
}
