/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:23:04 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/12 14:24:15 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_echo_loop(t_mini *test, int i)
{
	while (test->full_cmd[++i])
	{
		ft_putstr_fd(test->full_cmd[i], 1);
		if (!test->full_cmd[i + 1])
			break ;
		write(1, " ", 1);
	}
}

int	mini_echo(t_mini *test)
{
	int	i;
	int	option;

	if (ft_strncmp(test->ast[1], "T_OPTION", 8))
	{
		option = 1;
		mini_echo_loop(test, 0);
	}
	else
	{
		i = 2;
		while (!ft_strncmp(test->ast[i], "T_OPTION", 8))
			i++;
		option = 0;
		mini_echo_loop(test, i - 1);
	}
	return (write(1, "\n", option));
}

// int    mini_cd(t_mini test)
// {
//     char    *buf;
//     char    *tmp;
//     int        i;

//     i = 0;
//     buf = getcwd(NULL, 0);
//     if (test.ast[1] == NULL)
//     {
//         if (chdir(test.env->home) == -1)
//             return (1);
//     }
//     else if (!ft_strncmp(test.ast[1], "-", 1))
//     {
//         if (chdir(test.env->oldpwd) == -1)
//             return (1);
//     }
//     else if (chdir(test.ast[1]) == -1)
//         return (1);
//     tmp = getcwd(NULL, 0);
//     while (test.env->env[i])
//     {
//         if (!ft_strncmp(test.env->env[i], "OLDPWD=", 7))
//             test.env->env[i] = ft_strjoin("OLDPWD=", buf);
//         if (!ft_strncmp(test.env->env[i], "PWD=", 4))
//             test.env->env[i] = ft_strjoin("PWD=", tmp);
//         i++;
//     }
//     free(buf);
//     free(tmp);
//     return (0);
// }

int	mini_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
