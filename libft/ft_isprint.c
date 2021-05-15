/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:43:44 by dcordeli          #+#    #+#             */
/*   Updated: 2020/10/29 16:46:43 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

int	ft_allisprint(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0' && ft_isprint(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}
