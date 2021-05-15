/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/03 16:46:06 by dcordeli          #+#    #+#             */
/*   Updated: 2020/09/06 23:15:15 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "libft.h"

static int		ft_strcmp(char *s1, char *s2)
{
	int i;
	int l;

	i = 0;
	if (ft_strlen(s1) > ft_strlen(s2))
		l = ft_strlen(s2);
	else
		l = ft_strlen(s1);
	while (i < l)
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (s1[i] - s2[i]);
	}
	return (s1[i] - s2[i]);
}

static void		ft_sort_node(t_btree **node, int len, int k, int j)
{
	int		i;
	char	*tmpi;

	i = len - 1;
	while (i >= 0)
	{
		while (j <= i)
		{
			if (ft_strcmp(node[i]->key, node[i - j]->key) < 0)
			{
				tmpi = node[i]->key;
				node[i]->key = node[i - j]->key;
				node[i - j]->key = tmpi;
				tmpi = node[i]->item;
				node[i]->item = node[i - j]->item;
				node[i - j]->item = tmpi;
			}
			k = 0;
			j++;
		}
		i--;
		j = 1;
	}
}

static void		ft_balanced_tree(t_btree **node, int start, int end, int len)
{
	int mid;
	int mid_left;
	int mid_right;

	if (end < start)
		return ;
	mid = (end + start) / 2;
	mid_left = (mid - 1 + start) / 2;
	mid_right = (end + mid + 1) / 2;
	if (mid_left >= 0 && mid_left < len && mid > 0 &&
			mid != mid_left && mid_left >= start)
		node[mid]->left = node[mid_left];
	if (mid_right >= 0 && mid_right < len && mid < len &&
			mid != mid_right && mid_right <= end)
		node[mid]->right = node[mid_right];
	ft_balanced_tree(node, start, mid - 1, len);
	ft_balanced_tree(node, mid + 1, end, len);
}

static t_btree	**ft_search_root(t_btree **node, int start, int end)
{
	t_btree **root;
	int		mid;

	mid = (end + start) / 2;
	root = &node[mid];
	return (root);
}

t_btree			**ft_balance(t_btree **node, int len)
{
	t_btree **root;

	ft_sort_node(node, len, 0, 1);
	ft_balanced_tree(node, 0, len - 1, len);
	root = ft_search_root(node, 0, len - 1);
	return (root);
}
