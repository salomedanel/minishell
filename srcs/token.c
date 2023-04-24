/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:33:40 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/24 15:36:30 by sdanel           ###   ########.fr       */
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
	print_arg_ast(data);
}

void	print_arg_ast(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		printf("farg[%d] = %s \t\t\t ast[%d] = %d\n", i, data->f_arg[i], i,
			data->ast[i]);
		i++;
	}
}

int	init_ast(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
		i++;
	data->ast = malloc(sizeof(int) * (i));
	i = 0;
	while (data->f_arg[i])
	{
		data->ast[i] = -1;
		i++;
	}
	return (i);
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
		if (i != 0 && data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<' && is_builtin(data->f_arg[i - 1]) == 0)
			data->ast[i - 1] = T_CMD;
		if (i != 0 && data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<' && is_builtin(data->f_arg[i - 1]) == 1)
			data->ast[i - 1] = T_BUILTIN;
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
		if (data->ast[i] == -1 && i == 0 && is_builtin(data->f_arg[i]) == 0)
			data->ast[i] = T_CMD;
		if (data->ast[i] == -1 && data->ast[i - 1] == 0 && is_builtin(data->f_arg[i]) == 0)
			data->ast[i] = T_CMD;
		if (data->ast[i] == -1 && i == 0 && is_builtin(data->f_arg[i]) == 1)
			data->ast[i] = T_BUILTIN;
		if (data->ast[i] == -1 && data->ast[i - 1] == 0 && is_builtin(data->f_arg[i]) == 1)
			data->ast[i] = T_BUILTIN;
		if (data->ast[i] == -1 && data->f_arg[i][0] == '-')
			data->ast[i] = T_OPTION;
		else if (data->ast[i] == -1)
			data->ast[i] = T_WORD;
		i++;
	}
	return (0);
}
