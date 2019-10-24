/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 12:22:16 by twitting          #+#    #+#             */
/*   Updated: 2019/02/26 17:47:50 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	floorandceiling(t_wolf *w, int x)
{
	int y;

	y = 0;
	while (y < HWIN)
	{
		if (y <= w->drawstart)
		{
			w->color = w->teximg[8].data[y % SKYSIZE * SKYSIZE +
			((int)fabs(1.0 * w->skyangle) + x) % SKYSIZE];
			w->img.data[y * WWIN + x] = w->color;
		}
		y++;
	}
}

void	floortexcoords(t_wolf *w)
{
	if (w->side == 2)
	{
		w->floorxwall = w->mapx;
		w->floorywall = w->mapy + w->wallx;
	}
	else if (w->side == 0)
	{
		w->floorxwall = w->mapx + 1.0;
		w->floorywall = w->mapy + w->wallx;
	}
	else if (w->side == 3)
	{
		w->floorxwall = w->mapx + w->wallx;
		w->floorywall = w->mapy;
	}
	else if (w->side == 1)
	{
		w->floorxwall = w->mapx + w->wallx;
		w->floorywall = w->mapy + 1.0;
	}
}

void	drawfloor(t_wolf *w, int x)
{
	int y;

	x = (WWIN - 1) - x;
	y = w->drawend;
	floortexcoords(w);
	w->distplayer = 0.0;
	while (y < HWIN)
	{
		w->currentdist = HWIN / (2.0 * y - HWIN);
		w->weight = (w->currentdist - w->distplayer) /
		(w->perpwalldist - w->distplayer);
		w->currentfloorx = w->weight * w->floorxwall +
		(1.0 - w->weight) * w->posx;
		w->currentfloory = w->weight * w->floorywall +
		(1.0 - w->weight) * w->posy;
		w->floortexx = (int)(w->currentfloorx * TEXS) % TEXS;
		w->floortexy = (int)(w->currentfloory * TEXS) % TEXS;
		w->color = w->teximg[6].data[TEXS * w->floortexy + w->floortexx];
		w->img.data[y * WWIN + x] = w->color;
		y++;
	}
}

void	texcalc(t_wolf *w)
{
	if (w->side == 0 || w->side == 2)
		w->wallx = w->posy + w->perpwalldist * w->raydiry;
	else
		w->wallx = w->posx + w->perpwalldist * w->raydirx;
	w->wallx -= (int)(w->wallx);
	w->texx = (int)(w->wallx * (double)TEXS);
	if ((w->side == 0 || w->side == 2) && w->raydirx > 0)
		w->texx = TEXS - w->texx - 1;
	if ((w->side == 1 || w->side == 3) && w->raydiry < 0)
		w->texx = TEXS - w->texx - 1;
}

void	texdraw(t_wolf *w, int x)
{
	int	y;
	int	texy;

	if ((w->mapx == w->mapsizex) || (w->mapy == w->mapsizey) || (w->mapx < 0) ||
		(w->mapy < 0))
		w->texnum = 0;
	else
		w->texnum = w->map[w->mapy][w->mapx] - 1;
	y = w->drawstart;
	texcalc(w);
	while (y <= w->drawend)
	{
		texy = (((y - (HWIN / 2) + (w->lineheight / 2)) * TEXS)
		/ w->lineheight);
		w->color = w->teximg[w->texnum + (w->side / 2)].data[TEXS *
		texy + w->texx];
		if (w->side == 1 || w->side == 3)
			w->color /= 2;
		w->img.data[y * WWIN + x] = w->color;
		y++;
	}
	floorandceiling(w, x);
}
