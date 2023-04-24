/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdanel <sdanel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 11:41:14 by sdanel            #+#    #+#             */
/*   Updated: 2023/04/24 14:08:09 by sdanel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_sigint(int sig)
{
    (void) sig;
    printf("CTRL+C detected\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
  //  free_parsing_token(data);
}

void    handle_sigquit(int sig)
{
    (void) sig;
    printf("CTRL+D detected\n");
  //  free_parsing_token(data);
    exit (0);
}