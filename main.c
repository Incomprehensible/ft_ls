/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:11:17 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/18 03:01:52 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	sup_for_main(t_tree *tr, t_tree *er, t_tree *fi, t_bit *flag)
{
	if (flag->lgbt)
		play_song();
	tree_print(er, NULL, flag, 1);
	if (fi)
	{
		fi = tree_to_start(fi);
		fi = tree_controller(fi, flag);
	}
	print_file(fi, flag);
	tree_print(tr, NULL, flag, 0);
	tree_destroy(tr);
	tree_destroy(er);
	tree_destroy(fi);
	if (flag->lgbt)
		kill_song();
	free(flag);
}

int		main(int ac, char **av)
{
	t_bit	*flag;
	t_tree	*tree;
	t_tree	*tree_er;
	t_tree	*file;

	flag = create_flag(ac, av);
	print_lgbt(-1);
	tree_er = tree_invalid(av, flag);
	tree = tree_born(flag, ac, av);
	file = tree_file(flag, av);
	if (tree)
	{
		tree = tree_to_start(tree);
		tree = tree_controller(tree, flag);
	}
	if (tree_er)
	{
		tree_er = tree_to_start(tree_er);
		tree_sort(tree_er, ascii_sort);
		tree_er = tree_to_start(tree_er);
	}
	sup_for_main(tree, tree_er, file, flag);
	return (0);
}
