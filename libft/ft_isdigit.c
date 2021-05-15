/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:32:32 by dcordeli          #+#    #+#             */
/*   Updated: 2020/10/29 16:38:11 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	ft_allisdigit(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0' && ft_isdigit(s[i]))
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}
