/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_envbis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danelsalome <danelsalome@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:33:41 by danelsalome       #+#    #+#             */
/*   Updated: 2023/05/10 19:32:46 by danelsalome      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int len_env(char *arg, t_data *data)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (arg[i])
    {
        if (arg[i] == '$')
        {
           count = check_varenv(data, arg);
        }
        count++;
        i++;
    }
    printf("count = %d\n", count);
    return (count);
}

int var_in_env(char *arg, t_data *data)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 1;
    while (data->new_env[i])
    {
        while (data->new_env[i][j])
        {
            if (data->new_env[i][j] == '=')
            {
                j++;
                while (data->new_env[i][j] == arg[k])
                {
                    if 
                }
                
            }
        }
    }
}