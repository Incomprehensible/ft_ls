/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_func_for_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 04:08:21 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 06:46:17 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		path_and_total(t_tree *tree, t_bit *bit, char *name)
{
	int i;

	i = 0;
	if (one_or_not(tree, bit) && !tree->pre)
	{
		print_path(name);
		i = 1;
	}
	if (tree->par && !tree->pre)
	{
		print_total(tree, bit);
		i = 1;
	}
	return (i);
}

void	calc_row_col(int nbr, int max, int *col, int *row)
{
	t_win	win;

	ioctl(0, TIOCGWINSZ, &win);
	*col = win.ws_col / (max + 1);
	if (*col == 0)
		(*col)++;
	*row = nbr / *col;
	if (nbr % *col != 0)
		(*row)++;
	*col = nbr / *row;
	if (nbr % *row != 0)
		(*col)++;
}

int		print_me_please(t_tree *tree, t_bit *bit, int nbr, int max)
{
	t_tree	*print;
	int		col;
	int		row;
	int		i;

	i = 0;
	if (tree && bit && nbr)
	{
		calc_row_col(nbr, max, &col, &row);
		while (i < nbr)
		{
			if (bit->lgbt)
				print_lgbt(0);
			print = find_tree(tree, (i / col + (i % col) * row), bit);
			(print && (i / col + (i % col) * row) < nbr) ?
				ft_putstr(print->name) : nbr++;
			((i + 1) % col == 0 || i + 1 == nbr) ?
				ft_putchar('\n') : fill_space(print->name, max);
			i++;
		}
		print_lgbt(-666);
	}
	return (i);
}

int		prepar_for_print(t_tree *tree, t_bit *bit)
{
	int		max;
	int		nbr;

	if (tree && bit && tree->par)
	{
		nbr = count_tree(tree, bit);
		max = count_name_tree(tree, bit);
		return (print_me_please(tree, bit, nbr, max));
	}
	return (0);
}
