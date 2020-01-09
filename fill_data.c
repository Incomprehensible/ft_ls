/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bomanyte <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 20:04:29 by bomanyte          #+#    #+#             */
/*   Updated: 2019/07/16 06:06:40 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

static void		get_size_nd_time(t_tree *node, t_stat *buff)
{
	char		*buf;
	long int	copy;
	int			j;

	buf = ctime(&buff->st_mtime);
	copy = get_year(buf);
	j = get_month(buf);
	copy = j <= 9 ? copy * 100 + j : copy * 10 + j;
	j = 7;
	while (j != 19)
	{
		if (j == 8 && buf[j] == ' ')
			copy = copy * 10;
		else if (buf[j] >= 46 && buf[j] <= 57)
			copy = copy * 10 + (buf[j] - '0');
		j++;
	}
	node->data->time_hash = copy;
	node->data->time = time_to_str(buf);
	node->data->blocks = buff->st_blocks;
	node->data->type = (buff->st_mode & S_IFDIR) ? 2 : 1;
	node->data->size = buff->st_size;
	node->data->hd_link = buff->st_nlink;
}

static int		get_soft_ln(t_tree *node, t_stat *buff, char *path)
{
	char	*buf;
	ssize_t len;

	if (S_ISLNK(buff->st_mode))
	{
		len = buff->st_size;
		if (!(buf = (char *)malloc(len + 1)))
			exit(-1);
		if (readlink(path, buf, len) == -1)
		{
			free(buf);
			exit(-1);
		}
		buf[len] = '\0';
		node->data->soft_ln = buf;
		return (1);
	}
	node->data->soft_ln = NULL;
	return (0);
}

static void		get_rwx(char *buf, t_stat *buff)
{
	buf[1] = (buff->st_mode & S_IRUSR) ? 'r' : '-';
	buf[4] = (buff->st_mode & S_IRGRP) ? 'r' : '-';
	buf[7] = (buff->st_mode & S_IROTH) ? 'r' : '-';
	buf[2] = (buff->st_mode & S_IWUSR) ? 'w' : '-';
	buf[5] = (buff->st_mode & S_IWGRP) ? 'w' : '-';
	buf[8] = (buff->st_mode & S_IWOTH) ? 'w' : '-';
	buf[3] = (buff->st_mode & S_IXUSR) ? 'x' : '-';
	buf[6] = (buff->st_mode & S_IXGRP) ? 'x' : '-';
	buf[9] = (buff->st_mode & S_IXOTH) ? 'x' : '-';
}

static void		get_mode(t_tree *node, t_stat *buff, char *path)
{
	int		is_l;
	char	*buf;

	is_l = 0;
	buf = (char *)ft_memalloc(11);
	if ((is_l = get_soft_ln(node, buff, path)) == -1)
	{
		free(buf);
		file_set_zero(node, (int)errno);
		errno = 0;
		return ;
	}
	get_rwx(buf, buff);
	buf[0] = (buff->st_mode & S_IFDIR) ? 'd' : '-';
	buf[0] = is_l ? 'l' : buf[0];
	buf[3] = ((buf[3] == 'x') && (buff->st_mode & S_ISUID)) ? 's' : buf[3];
	buf[3] = ((buf[3] != 's') && (buf[3] != 'x')
			&& (buff->st_mode & S_ISUID)) ? 'S' : buf[3];
	buf[6] = ((buf[6] == 'x') && (buff->st_mode & S_ISUID)) ? 's' : buf[6];
	buf[6] = ((buf[6] != 's') && (buf[6] != 'x')
			&& (buff->st_mode & S_ISUID)) ? 'S' : buf[6];
	buf[9] = ((buf[9] == 'x') && (buff->st_mode & S_ISVTX)) ? 't' : buf[9];
	buf[9] = ((buf[9] != 'x') && (buf[9] != 't')
			&& (buff->st_mode & S_ISVTX)) ? 'T' : buf[9];
	node->data->rights = buf;
}

void			fill_data(t_tree *node, char *name)
{
	t_stat buff;

	if (errno || lstat(name, &buff) == -1)
	{
		file_set_zero(node, (int)errno);
		errno = 0;
		return ;
	}
	file_set_zero(node, (int)0);
	get_id(node, &buff);
	get_size_nd_time(node, &buff);
	get_mode(node, &buff, name);
}
