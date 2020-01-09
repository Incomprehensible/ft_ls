/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 20:47:14 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 06:29:51 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static void		time_ascii(t_tree *root, int (*s)(t_tree *, t_tree *))
{
	t_tree *p;

	p = root->next;
	while (p)
	{
		if (root->data->time_hash == p->data->time_hash
				&& ft_strcmp(root->name, p->name) > 0)
		{
			if (root->next == p)
				sort_next(root, p);
			else
				sort_not_next(root, p);
			root = p;
		}
		p = p->next;
	}
	if (!root->next)
		return ;
	return (time_ascii(root->next, s));
}

void			sort_t_ascii(t_tree *root, int (*s)(t_tree *, t_tree *))
{
	t_tree *p;

	if (!root)
		return ;
	if (!root->par)
		return (sort_t_ascii(root->chi, s));
	p = root;
	if (!p)
		return ;
	time_ascii(p, s);
	p = p->par->chi;
	while (p)
	{
		if (p->chi)
			time_ascii(p->chi, s);
		p = p->next;
	}
}

int				size_sort(t_tree *first, t_tree *second)
{
	if (first && second)
	{
		if (first->data->size > second->data->size)
			return (1);
		if (first->data->size < second->data->size)
			return (0);
		if (ascii_sort(first, second))
			return (1);
	}
	return (0);
}

int				ascii_sort(t_tree *first, t_tree *second)
{
	if (first && second)
	{
		if (ft_strcmp(first->name, second->name) > 0)
			return (1);
	}
	return (0);
}
