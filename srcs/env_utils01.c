/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:40:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/06/10 12:39:30 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	parse_var_to_unset(char *var)
{
	int	i;

	i = -1;
	if (!var)
		return (2);
	if (var[0] == '-')
		return (1);
	if (ft_isdigit(var[0]) == 1)
		return (2);
	while (var[++i])
	{
		if (ft_isspecialchar(var[i]) == 1)
			return (2);
		else if (var[i] == '=')
			return (2);
	}
	return (0);
}

int	unset_loop(t_data *data, int i, int j)
{
	int		k;
	int		len;
	char	*var;

	var = ft_strjoin(data->tmp_arg[j], "=");
	len = ft_strlen(var);
	k = -1;
	while (data->new_env[++k])
		if (!ft_strncmp(data->new_env[k], var, len))
			i--;
	free(var);
	return (i);
}

int	var_to_unset(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->new_env[i])
		i++;
	while (data->tmp_arg[++j])
	{
		if (parse_var_to_unset(data->tmp_arg[j]) == 1)
		{
			err_unset_opt(data->tmp_arg[j]);
			continue ;
		}
		else if (parse_var_to_unset(data->tmp_arg[j]) == 2)
		{
			err_unset_id(data->tmp_arg[j]);
			continue ;
		}
		else if (parse_var_to_unset(data->tmp_arg[j]) == 0)
			i = unset_loop(data, i, j);
	}
	return (i);
}

int	check_unset(char **var_to_unset, char *var_to_check)
{
	int		i;
	int		j;
	int		len;
	char	*var;

	j = 0;
	i = 0;
	while (var_to_unset[++i])
	{
		var = ft_strjoin(var_to_unset[i], "=");
		len = ft_strlen(var);
		if (!ft_strncmp(var_to_check, var, len))
			j++;
		free(var);
	}
	if (j > 0)
		return (1);
	return (0);
}
