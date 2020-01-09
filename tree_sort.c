/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:23:23 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/11 21:22:03 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	tree_swap(t_tree *tree1, t_tree *tree2)
{
	if (tree1 && tree2)
	{
		if (tree1->pre)
			tree1->pre->next = tree2;
		if (tree2->next)
			tree2->next->pre = tree1;
		tree2->pre = tree1->pre;
		tree1->next = tree2->next;
		tree2->next = tree1;
		tree1->pre = tree2;
		if (tree1->par && tree1->par->chi - tree1 == 0)
			tree1->par->chi = tree2;
	}
}

int		is_sort(t_tree *tree, int (*sort)(t_tree *, t_tree *))
{
	if (tree && sort)
	{
		while (tree->next)
		{
			if (sort(tree, tree->next))
				return (0);
			else
				tree = tree->next;
		}
	}
	return (1);
}

void	tree_sort(t_tree *tree, int (*sort)(t_tree *, t_tree *))
{
	t_tree *first;

	if (tree && sort)
	{
		while (!is_sort(tree, sort))
		{
			first = tree;
			while (first->next)
			{
				if (sort(first, first->next))
					tree_swap(first, first->next);
				else
					first = first->next;
			}
			tree = to_start(tree);
		}
		sort_my_child(tree, sort);
	}
}

void	sort_my_child(t_tree *tree, int (*sort)(t_tree *, t_tree *))
{
	if (tree && sort)
	{
		while (tree)
		{
			if (tree->chi)
				tree_sort(tree->chi, sort);
			tree = tree->next;
		}
	}
}
