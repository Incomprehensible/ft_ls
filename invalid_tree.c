/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 16:03:13 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/18 17:34:10 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

int		dir_valid(char *name)
{
	DIR		*fdir;

	if ((fdir = opendir(name)))
	{
		closedir(fdir);
		errno = 0;
		return (1);
	}
	else if (errno == ENOTDIR || errno == EACCES)
		return (1);
	return (0);
}

int		tree_error(t_tree *tree)
{
	int		error;

	error = 0;
	if (tree->data)
	{
		if (tree->data->error != 13 && tree->data->error != 0)
		{
			ft_putstr("ft_ls: ");
			ft_putstr(tree->name);
			ft_putstr(": ");
			ft_putstr(strerror(tree->data->error));
			ft_putchar('\n');
			error = 1;
		}
	}
	return (error);
}

void	print_error(t_tree *tree, char *name)
{
	char *path;

	path = make_path(name, tree->name);
	print_path(path);
	ft_putstr("ft_ls: ");
	ft_putstr(tree->name);
	ft_putstr(": ");
	ft_putstr(strerror(tree->data->error));
	ft_putchar('\n');
	free(path);
}

int		tree_error_13(t_tree *tree, char *name, t_bit *bit, int i)
{
	if (tree)
	{
		if (bit->a)
		{
			i = print_new_line(i);
			print_error(tree, name);
			return (1);
		}
		else if (tree->name[0] != '.')
		{
			i = print_new_line(i);
			print_error(tree, name);
			return (1);
		}
	}
	return (i);
}

t_tree	*tree_invalid(char **av, t_bit *bit)
{
	t_tree	*tree;
	int		i;

	i = 1;
	tree = NULL;
	while (av[i] && av[i][0] == '-' && av[i][1] != '\0')
		i++;
	while (av[i])
	{
		if (!dir_valid(av[i]))
		{
			tree = tree_addend(tree, tree_create(av[i]));
			bit->er = 1;
			file_set_zero(tree, errno);
			errno = 0;
		}
		i++;
	}
	return (tree);
}
