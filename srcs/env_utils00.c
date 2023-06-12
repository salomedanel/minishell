/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:01:04 by tmichel-          #+#    #+#             */
/*   Updated: 2023/06/10 12:39:44 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	dup_tab(char **tab1, char **tab2)
{
	int	i;

	i = -1;
	while (tab1[++i])
		tab2[i] = ft_strdup(tab1[i]);
	tab2[i] = NULL;
}

int	sizetab(char **tab)
{
	int	i;

	i = -1;
	if (!tab || !tab[0])
		return (0);
	while (tab[++i])
		;
	return (i);
}

int	parse_var_to_exp(char *var)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!var)
		return (2);
	if (var[0] == '-')
		return (1);
	if (ft_isdigit(var[0]) == 1 || var[0] == '=')
		return (2);
	while (var[++i] && var[i] != '=')
		if (ft_isspecialchar(var[i]) == 1)
			j++;
	if (j > 0)
		return (2);
	return (0);
}

int	count_var_to_exp(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->cmd_tab[++i])
	{
		if (parse_var_to_exp(data->cmd_tab[i]) == 0)
			count++;
		else if (parse_var_to_exp(data->cmd_tab[i]) == 1)
		{
			err_export_opt(data, i);
			continue ;
		}
		else if (parse_var_to_exp(data->cmd_tab[i]) == 2)
		{
			err_export_id(data, i);
			continue ;
		}
	}
	return (count);
}

int	export_exist(t_data *data, char *var)
{
	int	i;
	int	j;

	j = -1;
	while (data->new_env[++j])
	{
		i = 0;
		while (var[i])
		{
			if (var[i] == '=')
				break ;
			i++;
		}
		if (var[i] && ft_strncmp(data->new_env[j], var, i + 1) == 0)
		{
			free(data->new_env[j]);
			data->new_env[j] = ft_strdup(get_space(var));
			return (0);
		}
	}
	return (1);
}
