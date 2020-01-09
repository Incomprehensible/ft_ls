/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 05:52:00 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/17 01:07:53 by crycherd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

char			*time_to_str(char *buf)
{
	char	copy[13];
	int		i;
	int		j;

	copy[12] = '\0';
	i = 0;
	j = 4;
	while (i != 12)
	{
		copy[i] = buf[j];
		i++;
		j++;
	}
	return (ft_strdup(copy));
}

void			file_set_zero(t_tree *node, int err)
{
	node->data->user = NULL;
	node->data->group = NULL;
	node->data->hd_link = 0;
	node->data->time = NULL;
	node->data->size = 0;
	node->data->rights = NULL;
	node->data->error = err;
	node->data->type = 0;
	node->data->soft_ln = NULL;
	node->data->time_hash = 0;
}

void			get_id(t_tree *node, t_stat *buff)
{
	struct passwd	*user_id;
	struct group	*group_id;

	user_id = getpwuid(buff->st_uid);
	group_id = getgrgid(buff->st_gid);
	node->data->user = ft_strdup(user_id->pw_name);
	node->data->group = ft_strdup(group_id->gr_name);
}

int				get_month(const char *buf)
{
	char	month[4];
	int		res;

	month[0] = buf[4];
	month[1] = buf[5];
	month[2] = buf[6];
	month[3] = '\0';
	res = ft_strcmp(month, "Jan") ? 0 : 1;
	res = ft_strcmp(month, "Feb") ? res : 2;
	res = ft_strcmp(month, "Mar") ? res : 3;
	res = ft_strcmp(month, "Apr") ? res : 4;
	res = ft_strcmp(month, "May") ? res : 5;
	res = ft_strcmp(month, "Jun") ? res : 6;
	res = ft_strcmp(month, "Jul") ? res : 7;
	res = ft_strcmp(month, "Avg") ? res : 8;
	res = ft_strcmp(month, "Sep") ? res : 9;
	res = ft_strcmp(month, "Oct") ? res : 10;
	res = ft_strcmp(month, "Nov") ? res : 11;
	res = ft_strcmp(month, "Dec") ? res : 12;
	return (res);
}

int				get_year(const char *buf)
{
	int res;

	buf = buf + 19;
	if (*buf == ' ')
		buf++;
	res = *buf++ - '0';
	while (*buf != '\n')
	{
		res = res * 10 + (*buf - '0');
		buf++;
	}
	return (res);
}
