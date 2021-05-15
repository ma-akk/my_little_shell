/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcordeli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 21:03:25 by dcordeli          #+#    #+#             */
/*   Updated: 2021/03/31 21:03:27 by dcordeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree		*btree_create_node(void *key, void *item)
{
	t_btree	*elem;

	elem = (t_btree *)malloc(sizeof(t_btree));
	elem->key = key;
	elem->item = item;
	elem->left = NULL;
	elem->right = NULL;
	return (elem);
}

void		btree_apply_prefix(t_btree *root, void (*applyf)(t_btree *))
{
	(*applyf)(root);
	if (root->left != 0)
		btree_apply_prefix(root->left, applyf);
	if (root->right != 0)
		btree_apply_prefix(root->right, applyf);
}

void		btree_apply_infix(t_btree *root, void (*applyf)(t_btree *))
{
	if (root->left != 0)
		btree_apply_infix(root->left, applyf);
	(*applyf)(root);
	if (root->right != 0)
		btree_apply_infix(root->right, applyf);
}

void		btree_apply_suffix(t_btree *root, void (*applyf)(t_btree *))
{
	if (root->left != 0)
		btree_apply_suffix(root->left, applyf);
	if (root->right != 0)
		btree_apply_suffix(root->right, applyf);
	(*applyf)(root);
}
