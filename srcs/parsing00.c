/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:05 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/12 18:47:31 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_metachar(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	if (c == 32)
		return (2);
	return (0);
}

int	count_metachar(char *prompt)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (prompt[i])
	{
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 0
			&& is_metachar(prompt[i + 1]) == 0)
			count = count + 2;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 0
			&& is_metachar(prompt[i + 1]) == 2)
			count++;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 2
			&& is_metachar(prompt[i + 1]) == 0)
			count++;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 0
			&& is_metachar(prompt[i + 1]) == 1)
			count++;
		if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i - 1]) == 1
			&& is_metachar(prompt[i + 1]) == 0)
			count++;
		i++;
	}
	return (count);
}

int	add_space(char *prompt, char *new_prompt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (prompt[i])
	{
		if (is_metachar(prompt[i + 1]) == 1 && is_metachar(prompt[i]) != 2
			&& is_metachar(new_prompt[j - 1]) != 2 && i != 0)
		{
			new_prompt[j] = prompt[i];
			new_prompt[++j] = 32;
		}
		else if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i + 1]) != 2
			&& is_metachar(prompt[i + 1]) != 1)
		{
			new_prompt[j] = prompt[i];
			new_prompt[++j] = 32;
		}
		else
			new_prompt[j] = prompt[i];
		i++;
		j++;
	}
	return (j);
}

char	*clean_prompt(char *prompt)
{
	char	*new_prompt;
	int		i;

	new_prompt = malloc(sizeof(char) * (ft_strlen(prompt)
				+ count_metachar(prompt)) + 1);
	i = add_space(prompt, new_prompt);
	new_prompt[i] = '\0';
	free(prompt);
	return (new_prompt);
}

void	split_input(char *prompt)
{
	t_data	data;
	int		i;
	int		qtype;

	data.new_prompt = clean_prompt(prompt);
	i = 0;
	qtype = 0;
	while (data.new_prompt[i])
	{
		if (data.new_prompt[i] == '"' && (qtype == 0 || qtype == 2))
		{
			qtype = 2;
			if (space_dquotes(&data) == 1)
			{
				printf("%d\n", space_dquotes(&data));
				printf("minishell: syntax error near unexpected token `newline'\n");
				return ;
			}
		}
		else if (data.new_prompt[i] == '\'' && (qtype == 0 || qtype == 1))
		{
			qtype = 1;
			if (space_squotes(&data) == 1)
			{
				printf("%d\n", space_dquotes(&data));
				printf("minishell: syntax error near unexpected token `newline'\n");
				return ;
			}
		}
		i++;
	}
	//space_dquotes(&data);
	printf("%s\n", data.new_prompt);
}
