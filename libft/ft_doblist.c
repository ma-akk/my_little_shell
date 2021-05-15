/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_doblist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 21:22:56 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 21:23:00 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_doblist		*ft_doblstnew(void *content)
{
	t_doblist	*list;

	list = (t_doblist *)malloc(sizeof(t_doblist));
	if (NULL == list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

void			ft_doblstadd_front(t_doblist **lst, t_doblist *new)
{
	t_doblist	*tmp;

	if (new == NULL || lst == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		(*lst)->prev = new;
		tmp = (*lst);
		(*lst) = new;
		(*lst)->next = tmp;
	}
}
