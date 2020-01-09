/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lgbt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crycherd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 03:36:25 by crycherd          #+#    #+#             */
/*   Updated: 2019/07/16 09:45:32 by bomanyte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libls.h"

void	print_lgbt(int f)
{
	static int i;

	if (f == -666)
	{
		ft_putstr("\033[0m");
		return ;
	}
	i = f ? 0 : ++i;
	if (i > 0)
	{
		if (i % 6 == 0)
			ft_putstr("\x1B[31m");
		if (i % 6 == 1)
			ft_putstr("\x1B[91m");
		if (i % 6 == 2)
			ft_putstr("\x1B[93m");
		if (i % 6 == 3)
			ft_putstr("\x1B[92m");
		if (i % 6 == 4)
			ft_putstr("\x1B[34m");
		if (i % 6 == 5)
			ft_putstr("\x1B[35m");
	}
}

void	play_song(void)
{
	system("curl -sL http://tiny.cc/3twr9y --output .ok.mp3 2> /dev/null");
	system("afplay -v 1 .ok.mp3 2> /dev/null &");
}

void	kill_song(void)
{
	system("kill $(ps | grep .ok.mp3 | grep afplay | awk '{print $1}')");
}
