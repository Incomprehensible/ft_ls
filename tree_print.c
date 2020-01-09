/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 14:26:37 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/18 16:54:40 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		for_l(t_tree *tree, char *name, t_bit *bit)
{
	int	i;

	i = 0;
	while (tree)
	{
		if (bit->lgbt)
			print_lgbt(0);
		if ((tree_error(tree)))
		{
			tree = tree->next;
			i = 1;
			continue ;
		}
		i += path_and_total(tree, bit, name);
		if (bit_a_l(tree, bit))
			i = 1;
		tree = tree->next;
	}
	print_lgbt(-666);
	return (i);
}

int		not_for_l(t_tree *tree, char *name, t_bit *bit)
{
	char	*path;
	int		i;

	i = 0;
	path = make_path(name, tree->name);
	if (bit->lgbt)
		print_lgbt(0);
	if (one_or_not(tree, bit) && !tree->pre)
	{
		i = 1;
		print_path(name);
	}
	free(path);
	i += prepar_for_print(tree, bit);
	return (i);
}

int		print_invalid(t_tree *tree)
{
	int i;

	i = 0;
	while (tree)
	{
		i += tree_error(tree);
		tree = tree->next;
	}
	return (i);
}

int		tree_print(t_tree *tree, char *name, t_bit *bit, int er)
{
	int		i;

	if (!(i = 0) && tree)
	{
		if (er && !bit->l)
			print_invalid(tree);
		i = bit->l ? for_l(tree, name, bit) : not_for_l(tree, name, bit);
		while (tree)
		{
			if (tree->data && tree->data->error == 13)
			{
				if (bit->lgbt)
					print_lgbt(0);
				i = tree_error_13(tree, name, bit, i);
			}
			if (tree->chi)
			{
				i = print_if_will(i, bit, tree);
				i += print_chi(tree, name, bit, er);
			}
			tree = tree->next;
		}
	}
	return (i);
}
