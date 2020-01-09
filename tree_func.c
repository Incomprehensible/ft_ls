/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 01:10:41 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 05:45:29 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

t_tree	*tree_create(char *name)
{
	t_tree *new;

	new = NULL;
	if ((new = (t_tree*)malloc(sizeof(t_tree))))
	{
		new->name = ft_strdup(name);
		new->data = (t_data *)malloc(sizeof(t_data));
		new->par = NULL;
		new->chi = NULL;
		new->next = NULL;
		new->pre = NULL;
	}
	return (new);
}

t_tree	*tree_addend(t_tree *start, t_tree *new)
{
	if (start)
	{
		while (start->next)
			start = start->next;
		start->next = new;
		new->pre = start;
		new->par = start->par;
	}
	return (new);
}

t_tree	*tree_addend_chil(t_tree *root, t_tree *leaf)
{
	leaf = tree_addend(root->chi, leaf);
	if (!root->chi)
	{
		root->chi = leaf;
		leaf->par = root;
	}
	return (leaf);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->rights)
			free(data->rights);
		if (data->soft_ln)
			free(data->soft_ln);
		if (data->user)
			free(data->user);
		if (data->group)
			free(data->group);
		if (data->time)
			free(data->time);
	}
}

void	tree_destroy(t_tree *tree)
{
	if (tree)
	{
		tree_destroy(tree->next);
		tree_destroy(tree->chi);
		if (tree->data)
		{
			free_data(tree->data);
			free(tree->data);
		}
		free(tree->name);
		free(tree);
	}
}
