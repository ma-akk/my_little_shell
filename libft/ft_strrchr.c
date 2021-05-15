/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 16:25:44 by dcordeli          #+#    #+#             */
/*   Updated: 2020/11/04 20:07:07 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*u;
	int			i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s) - 1;
	u = s;
	if ((char)c == '\0')
	{
		u = u + i + 1;
		return ((char *)u);
	}
	while (i != 0 && s[i] != (char)c && s[i] != 0)
		i--;
	if (s[i] == (char)c)
	{
		u = u + i;
		return ((char *)u);
	}
	else
		return (NULL);
}

int		ft_strchr_i(const char *s, int c)
{
	const char	*u;
	int			i;

	if (s == NULL)
		return (-1);
	i = 0;
	u = s;
	if ((char)c == '\0')
	{
		u = u + ft_strlen(s);
		return ((int)ft_strlen(u));
	}
	while (i != (int)ft_strlen(s) - 1 && s[i] != (char)c && s[i] != 0)
		i++;
	if (s[i] == (char)c)
	{
		u = u + i;
		return (i);
	}
	else
		return (-1);
}
