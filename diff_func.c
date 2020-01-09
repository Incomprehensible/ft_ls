/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 21:32:03 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/17 01:29:09 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		one_or_not(t_tree *tree, t_bit *bit)
{
	int result;

	result = 0;
	if (tree && bit)
	{
		if (bit->er)
			result = 1;
		if (tree->par)
		{
			tree = tree->par;
			if (tree->next || tree->pre || tree->par)
				result = 1;
		}
	}
	return (result);
}

t_tree	*to_start(t_tree *tree)
{
	if (tree)
	{
		while (tree->pre)
			tree = tree->pre;
	}
	return (tree);
}

t_tree	*tree_to_start(t_tree *tree)
{
	if (tree)
	{
		while (tree->par)
			tree = tree->par;
		while (tree->pre)
			tree = tree->pre;
	}
	return (tree);
}

int		bit_a_l(t_tree *tree, t_bit *bit)
{
	if (tree && bit)
	{
		if (tree->par)
		{
			if (bit->a)
			{
				print_str_l(tree, bit);
				return (1);
			}
			else if (tree->name[0] != '.')
			{
				print_str_l(tree, bit);
				return (1);
			}
		}
	}
	return (0);
}

int		bit_a(t_tree *tree, t_bit *bit)
{
	if (tree && bit)
	{
		if (tree->par)
		{
			if (bit->a)
			{
				print_name(tree->name);
				return (1);
			}
			else if (tree->name[0] != '.')
			{
				print_name(tree->name);
				return (1);
			}
		}
	}
	return (0);
}
