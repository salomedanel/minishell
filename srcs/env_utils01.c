/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:40:11 by sdanel            #+#    #+#             */
/*   Updated: 2023/05/29 18:40:49 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_to_unset(t_data *data)
{
	int		i;
	int		j;
	int		k;
	int		len;
	char	*var;

	i = 0;
	j = 0;
	while (data->new_env[i])
		i++;
	while (data->tmp_arg[++j])
	{
		var = ft_strjoin(data->tmp_arg[j], "=");
		len = ft_strlen(var);
		k = -1;
		while (data->new_env[++k])
			if (!ft_strncmp(data->new_env[k], var, len))
				i--;
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
	}
	if (j > 0)
		return (1);
	return (0);
}
