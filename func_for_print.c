/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_for_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 04:04:26 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 04:17:45 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		print_new_line(int i)
{
	if (i)
	{
		ft_putchar('\n');
		i = 0;
	}
	return (i);
}

int		count_tree(t_tree *tree, t_bit *bit)
{
	int res;

	res = 0;
	if (tree)
	{
		while (tree)
		{
			if (bit->a)
				res++;
			else if (tree->name[0] != '.')
				res++;
			tree = tree->next;
		}
	}
	return (res);
}

int		count_name_tree(t_tree *tree, t_bit *bit)
{
	int	res;
	int nbr;

	res = 0;
	if (tree)
	{
		while (tree)
		{
			nbr = 0;
			if (bit->a)
				nbr = ft_strlen(tree->name);
			else if (tree->name[0] != '.')
				nbr = ft_strlen(tree->name);
			if (nbr > res)
				res = nbr;
			tree = tree->next;
		}
	}
	return (res);
}

t_tree	*find_tree(t_tree *tree, int n, t_bit *bit)
{
	int i;

	if (tree)
	{
		i = 0;
		while (tree->next && i <= n)
		{
			if (bit->a)
				i++;
			else if (tree->name[0] != '.')
				i++;
			if (i > n)
				break ;
			tree = tree->next;
		}
	}
	return (tree);
}

void	fill_space(char *name, int max)
{
	int i;

	if (name)
	{
		i = ft_strlen(name);
		while (i <= max)
		{
			ft_putchar(' ');
			i++;
		}
	}
}
