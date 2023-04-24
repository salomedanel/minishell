/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:29:32 by tmichel-          #+#    #+#             */
/*   Updated: 2023/04/24 18:28:07 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	set_pwd(t_data *data)
{
	int		i;

	i = 0;
	while (data->new_env[i])
	{
		if (!ft_strncmp(data->new_env[i], "PWD=", 4))
		{
			free(data->new_env[i]);
			data->new_env[i] = ft_strjoin("PWD=", getcwd(NULL, 0));
			break ;
		}
		i++;
	}
}

void	set_old_pwd(t_data *data)
{
	int		i;

	i = 0;
	while (data->new_env[i])
	{
		if (!ft_strncmp(data->new_env[i], "OLDPWD=", 7))
		{
			free(data->new_env[i]);
			data->new_env[i] = ft_strjoin("OLDPWD=", getcwd(NULL, 0));
			break ;
		}
		i++;
	}
}

int	count_args(t_data *data)
{
	int	i;

	i = 0;
	while (data->arg[i])
		i++;
	return (i);
}

void	exec_cd(t_data *data)
{
	if (!chdir(data->arg[1]))
	{
		set_old_pwd(data);
		set_pwd(data);
	}
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(data->f_arg[1], 2);
		ft_putstr_fd(" No such file or directory", 2);
	}	
}

int	mini_cd(t_data *data)
{
	int		i;
	char	*tmp;

	i = count_args(data);
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (i == 1)
	{
		set_old_pwd(data);
		tmp = ft_strdup("~");
		chdir(tmp);
		free(tmp);
		set_pwd(data);
	}
	else
		exec_cd(data);
	return (g_exit_code);
}
