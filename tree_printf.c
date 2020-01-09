/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 16:07:43 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/18 15:49:33 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static void		print_par_l(t_data *data, long long n, unsigned short n1)
{
	ft_putstr(data->rights);
	ft_putchar(' ');
	print_hd_link(data, n1);
	ft_putlongnbr(data->hd_link);
	ft_putchar(' ');
	ft_putstr(data->user);
	ft_putstr("  ");
	ft_putstr(data->group);
	ft_putchar(' ');
	print_size(data, n);
	ft_putlongnbr(data->size);
	ft_putchar(' ');
	ft_putstr(data->time);
	ft_putchar(' ');
}

void			print_path(char *path)
{
	if (path)
	{
		ft_putstr(path);
		ft_putstr(":\n");
	}
}

void			print_name(char *name)
{
	if (name)
	{
		ft_putstr(name);
		ft_putchar('\t');
	}
}

void			print_str_l(t_tree *tree, t_bit *bit)
{
	long long		n;
	unsigned short	n1;

	n = max_size(tree, bit);
	n1 = max_link(tree, bit);
	if (tree)
	{
		print_par_l(tree->data, n, n1);
		ft_putstr(tree->name);
		ft_putchar('\n');
	}
}

void			print_total(t_tree *tree, t_bit *bit)
{
	if (tree && ((tree->par->chi && bit->a) ||
		((tree->par->chi && ((tree->par->chi->name[0] != '.') ||
		(tree->par->chi->next && (tree->par->chi->next->name[0] != '.')) ||
		(tree->par->chi->next->next &&
		tree->par->chi->next->next->name[0] != '.') ||
		(tree->par->chi->next->next && tree->par->chi->next->next->next))))))
	{
		ft_putstr("total ");
		ft_putnbr(tree->par->data->blocks);
		ft_putchar('\n');
	}
}
