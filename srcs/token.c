/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:33:40 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/21 15:46:25 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token(t_data *data)
{
	init_ast(data);
	if (token_metachar(data) == -1)
		return ;
	if (token_word_metachar(data) == -1)
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

void	init_ast(t_data *data)
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

// modifier les conditions pour verifier i + 1 et i - 1

int	token_word_metachar(t_data *data)
{
	int	i;

	i = 0;
	while (data->f_arg[i])
	{
		if (data->f_arg[i][0] == '>' && data->ast[i] != 1)
			data->ast[i + 1] = T_OUTFILE_TRUNC;
		if (data->f_arg[i][0] == '<' && data->ast[i] != 2)
			data->ast[i - 1] = T_INFILE;
		if (data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<'
			&& data->ast[i] != 3)
			data->ast[i + 1] = T_LIMITER;
		if (data->f_arg[i][0] == '<' && data->f_arg[i][1] == '<'
			&& data->ast[i] != 3)
			data->ast[i - 1] = T_CMD;
		if (data->f_arg[i][0] == '>' && data->f_arg[i][1] == '>'
			&& data->ast[i] != 4)
			data->ast[i + 1] = T_OUTFILE_APPEND;
		i++;
	}
	return (0);
}

// Ensuite regarder si ast = -1. Si oui et que mot au debut ou apres un pipe => CMD.
// Pour les restes des -1 = OPTION