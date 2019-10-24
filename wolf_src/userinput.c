/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:58:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/26 17:32:50 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	rotation(t_wolf *w)
{
	double	tempx;
	double	temppl;

	if (w->righttoggler == 1 && w->lefttoggler == 0)
	{
		tempx = w->dirx;
		w->dirx = tempx * cos(ANG) - w->diry * sin(ANG);
		w->diry = tempx * sin(ANG) + w->diry * cos(ANG);
		temppl = w->planex;
		w->planex = temppl * cos(ANG) - w->planey * sin(ANG);
		w->planey = temppl * sin(ANG) + w->planey * cos(ANG);
		w->skyangle += w->skyangle == 3840 ? -3808 : 32;
	}
	if (w->lefttoggler == 1 && w->righttoggler == 0)
	{
		tempx = w->dirx;
		w->dirx = tempx * cos(ANG) + w->diry * sin(ANG);
		w->diry = -tempx * sin(ANG) + w->diry * cos(ANG);
		temppl = w->planex;
		w->planex = temppl * cos(ANG) + w->planey * sin(ANG);
		w->planey = -temppl * sin(ANG) + w->planey * cos(ANG);
		w->skyangle -= w->skyangle == 0 ? -3808 : 32;
	}
}

void	moving(t_wolf *w)
{
	if (w->uptoggler == 1 && w->downtoggler == 0)
	{
		if ((w->posx + w->dirx * 0.3 >= 0) && (w->posx +
		w->dirx * 0.3 < w->mapsizex) &&
		(w->map[(int)w->posy][(int)(w->posx + w->dirx * 0.3)] == 0))
			w->posx += w->dirx * 0.1;
		if ((w->posy + w->diry * 0.3 >= 0) && (w->posy +
		w->diry * 0.3 < w->mapsizey) &&
		(w->map[(int)(w->posy + w->diry * 0.3)][(int)w->posx] == 0))
			w->posy += w->diry * 0.1;
	}
	if (w->downtoggler == 1 && w->uptoggler == 0)
	{
		if ((w->posx - w->dirx * 0.3 >= 0) && (w->posx - w->dirx * 0.3
		< w->mapsizex) &&
		(w->map[(int)w->posy][(int)(w->posx - w->dirx * 0.3)] == 0))
			w->posx -= w->dirx * 0.1;
		if ((w->posy - w->diry * 0.3 >= 0) && (w->posy - w->diry * 0.3
		< w->mapsizey) &&
		(w->map[(int)(w->posy - w->diry * 0.3)][(int)w->posx] == 0))
			w->posy -= w->diry * 0.1;
	}
	rotation(w);
}

int		crossclose(void *param)
{
	(void)param;
	system("killall afplay");
	exit(0);
	return (0);
}

int		key_press(int key, t_wolf *w)
{
	if (key == KEY_UP)
		if (w->uptoggler == 0)
			w->uptoggler = 1;
	if (key == KEY_DOWN)
		if (w->downtoggler == 0)
			w->downtoggler = 1;
	if (key == KEY_LEFT)
		if (w->lefttoggler == 0)
			w->lefttoggler = 1;
	if (key == KEY_RIGHT)
		if (w->righttoggler == 0)
			w->righttoggler = 1;
	if (key == KEY_SPACE)
		if (w->swing == 0)
			w->swing = 1;
	return (0);
}

int		key_release(int key, t_wolf *w)
{
	if (key == KEY_UP)
		w->uptoggler = 0;
	if (key == KEY_DOWN)
		w->downtoggler = 0;
	if (key == KEY_LEFT)
		w->lefttoggler = 0;
	if (key == KEY_RIGHT)
		w->righttoggler = 0;
	if (key == KEY_SPACE)
		w->swing = 0;
	if (key == KEY_ESCAPE)
	{
		system("killall afplay");
		exit(0);
	}
	return (0);
}
