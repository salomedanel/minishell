/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_revenge.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:29:32 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/24 14:59:34 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	mini_cd(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->arg[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (i == 1)
	{
		tmp = ft_strdup("~");
		chdir(tmp);
		free(tmp);
	}
	else
		chdir(data->arg[1]);
	return (g_exit_code);
}

//reprendre avec OLDPWD/PWD cf man

