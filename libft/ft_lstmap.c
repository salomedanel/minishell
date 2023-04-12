/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmichel- <tmichel-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:19:45 by tmichel-          #+#    #+#             */
/*   Updated: 2022/11/20 22:55:54 by tmichel-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*nextelem;

	if (!f || !del || !lst)
		return (NULL);
	new = NULL;
	while (lst)
	{
		nextelem = ft_lstnew((*f)(lst->content));
		if (!nextelem)
		{
			ft_lstclear(&lst, del);
			free(new);
			return (NULL);
		}
		ft_lstadd_back(&new, nextelem);
		lst = lst->next;
	}
	return (new);
}
