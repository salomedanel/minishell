/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:05 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/24 12:49:19 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_metachar(char *prompt)
{
	int	count;
	int	i;

	i = 1;
	count = 0;
	if (prompt == NULL)
		return (0);
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
	if (prompt == NULL)
		return (0);
	while (prompt[i])
	{
		if (is_metachar(prompt[i + 1]) == 1 && is_metachar(prompt[i]) != 2
			&& (prompt[i] != prompt[i + 1]))
			j = cpy_prompt(prompt, new_prompt, j, i);
		else if (is_metachar(prompt[i]) == 1 && is_metachar(prompt[i + 1]) != 2
			&& is_metachar(prompt[i + 1]) != 1)
			j = cpy_prompt(prompt, new_prompt, j, i);
		else
			new_prompt[j] = prompt[i];
		if (j == ft_strlen(prompt) + count_metachar(prompt))
			return (j);
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

void	split_input(char *prompt, char **env)
{
	t_data	data;
	int		i;

	i = -1;
	dup_env(&data, env);
	data.clean_prompt = clean_prompt(prompt);
	data.clean_prompt = handle_quotes(&data, i);
	if (data.clean_prompt == NULL)
		return ;
	split_space(&data, i);
	final_arg(&data);
	token(&data);
	return ;
}
