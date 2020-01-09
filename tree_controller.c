/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 18:52:59 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/17 07:26:11 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		print_if_will(int i, t_bit *bit, t_tree *tree)
{
	if (tree && bit)
	{
		if (bit->a)
		{
			if (i)
				i = print_new_line(i);
		}
		else
		{
			if (i && tree->name[0] != '.')
				i = print_new_line(i);
		}
	}
	return (i);
}

t_tree	*reverse_me(t_tree *tree)
{
	t_tree	*swap;
	t_tree	*node;

	swap = tree;
	if (tree)
	{
		node = NULL;
		while (swap->next)
			swap = swap->next;
		if (swap->par)
			swap->par->chi = swap;
		swap->next = swap->pre;
		while (swap->next)
		{
			swap->next = swap->pre;
			swap->pre = node;
			node = swap;
			if (swap->next)
				swap = swap->next;
		}
		while (swap->pre)
			swap = swap->pre;
	}
	tree = swap;
	return (tree);
}

void	reverse_tree(t_tree *root)
{
	t_tree	*start;

	if (root)
	{
		start = root;
		start = reverse_me(start);
		while (start)
		{
			if (start->chi)
				reverse_tree(start->chi);
			start = start->next;
		}
	}
}

t_tree	*tree_controller(t_tree *root, t_bit *flags)
{
	flags->a ? get_totalr(root) : get_total(root);
	tree_sort(root, ascii_sort);
	if (flags->t)
	{
		sort_t(root);
		sort_t_ascii(root, ascii_sort);
	}
	if (flags->s)
		tree_sort(root, size_sort);
	root = tree_to_start(root);
	if (flags->r)
		reverse_tree(root);
	root = tree_to_start(root);
	return (root);
}
