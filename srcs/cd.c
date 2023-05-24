/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 13:29:32 by tmichel-          #+#    #+#             */
/*   Updated: 2023/05/24 14:52:50 by tmichel-         ###   ########.fr       */
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
	while (data->tmp_arg[i])
		i++;
	return (i);
}

void	exec_cd(t_data *data)
{
	set_old_pwd(data);
	if (!chdir(data->tmp_arg[1]))
		set_pwd(data);
	else
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(data->tmp_arg[1], 2);
		ft_putstr_fd(" No such file or directory\n", 2);
	}	
}

int	mini_cd(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = count_args(data);
	j = -1;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (i == 1)
	{
		while (data->new_env[++j])
		{
			if (!ft_strncmp(data->new_env[j], "HOME=", 5))
			{
				set_old_pwd(data);
				tmp = ft_strdup(data->new_env[j] + 5);
				chdir(tmp);
				free(tmp);
				set_pwd(data);
				break ;
			}
		}
	}
	else
		exec_cd(data);
	return (g_exit_code);
}
