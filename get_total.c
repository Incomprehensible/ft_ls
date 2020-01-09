/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_total.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 06:34:27 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/16 06:34:47 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

long long	get_total(t_tree *root)
{
	if (!root->par || (root->name[0] != '.' &&
				!(ft_strncmp(root->name, "..", PATH_MAX) == 0 ||
					(ft_strncmp(root->name, ".", PATH_MAX) == 0))))
	{
		if (root->par)
			root->par->data->blocks += root->data->blocks;
		if (root->chi)
			root->data->blocks += get_total(root->chi);
		if (root->next)
		{
			root = root->next;
			get_total(root);
			return (root->data->blocks);
		}
		if (!root->next && !root->chi)
			return (root->data->blocks);
	}
	if (root->next)
		get_total(root->next);
	return (0);
}

long long	get_totalr(t_tree *root)
{
	if (root->par)
		root->par->data->blocks += root->data->blocks;
	if (root->chi)
		root->data->blocks += get_totalr(root->chi);
	if (root->next)
	{
		root = root->next;
		get_totalr(root);
		return (root->data->blocks);
	}
	if (!root->next && !root->chi)
		return (root->data->blocks);
	return (0);
}
