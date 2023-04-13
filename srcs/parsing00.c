/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:05 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/13 14:15:02 by sdanel           ###   ########.fr       */
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
	if (is_metachar(prompt[0]) == 1)
		count--;
	if (is_metachar(prompt[ft_strlen(prompt) - 1]) == 1)
		count--;
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
			&& (prompt[i] != prompt[i + 1]))
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
	printf("%d\n", count_metachar(prompt));
	i = add_space(prompt, new_prompt);
	new_prompt[i] = '\0';
	free(prompt);
	return (new_prompt);
}

void	split_input(char *prompt)
{
	t_data	data;

	data.clean_prompt = clean_prompt(prompt);
	data.final_prompt = malloc(sizeof(char) * ft_strlen(data.clean_prompt));
	data.final_prompt = handle_quotes(&data);
	if (data.final_prompt == NULL)
		return ;
	split_space(data.final_prompt);
	printf("%s\n", data.final_prompt);
	free(data.clean_prompt);
}
