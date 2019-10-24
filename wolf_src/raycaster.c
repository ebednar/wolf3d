/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 14:59:41 by twitting          #+#    #+#             */
/*   Updated: 2019/02/27 15:50:21 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	sidecalc(t_wolf *w)
{
	if (w->raydirx < 0)
	{
		w->stepx = -1;
		w->sidedistx = (w->posx - w->mapx) * w->deltadistx;
	}
	else
	{
		w->stepx = 1;
		w->sidedistx = (w->mapx + 1.0 - w->posx) * w->deltadistx;
	}
	if (w->raydiry >= 0)
	{
		w->stepy = 1;
		w->sidedisty = (w->mapy + 1.0 - w->posy) * w->deltadisty;
	}
	else
	{
		w->stepy = -1;
		w->sidedisty = (w->posy - w->mapy) * w->deltadisty;
	}
}

void	findhit(t_wolf *w)
{
	while (w->hit == 0)
	{
		if (w->sidedistx < w->sidedisty)
		{
			w->sidedistx += w->deltadistx;
			w->mapx += w->stepx;
			w->side = w->raydirx < 0 ? 0 : 2;
		}
		else
		{
			w->sidedisty += w->deltadisty;
			w->mapy += w->stepy;
			w->side = w->raydiry < 0 ? 1 : 3;
		}
		if ((w->mapx == w->mapsizex) || (w->mapy == w->mapsizey) ||
		(w->mapx < 0) || (w->mapy < 0) || (w->map[w->mapy][w->mapx] > 0
		&& w->map[w->mapy][w->mapx] < 10))
			w->hit = 1;
	}
	if (w->side == 0 || w->side == 2)
		w->perpwalldist = (double)(w->mapx - w->posx + (1 - w->stepx) / 2.0)
		/ w->raydirx;
	else
		w->perpwalldist = (double)(w->mapy - w->posy + (1 - w->stepy) / 2.0)
		/ w->raydiry;
}

void	drawline(t_wolf *w, int x)
{
	x = (WWIN - 1) - x;
	w->zbuffer[x] = w->perpwalldist;
	w->lineheight = (int)(HWIN / w->perpwalldist);
	w->drawstart = -1 * w->lineheight / 2 + HWIN / 2;
	if (w->drawstart < 0)
		w->drawstart = 0;
	w->drawend = w->lineheight / 2 + HWIN / 2;
	if (w->drawend >= HWIN)
		w->drawend = HWIN - 1;
	texdraw(w, x);
}

void	fps(t_wolf *w)
{
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->img.img_ptr, 0, 0);
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr,
	w->teximg[11 + w->swing].img_ptr, WWIN / 2 - 700, HWIN - 930);
	if (w->swing == 1)
		w->swing = 2;
	w->fps++;
	w->timer += (clock() - w->frame) / CLOCKS_PER_SEC;
	if (w->timer >= 1.0)
	{
		ft_putstr("fps = ");
		ft_putnbr(w->fps);
		ft_putchar('\n');
		w->oldfps = w->fps;
		w->fps = 0;
		w->timer -= 1;
		if ((w->uptoggler == 1 && w->downtoggler == 0) ||
		(w->downtoggler == 1 && w->uptoggler == 0))
			system("afplay sound/step.mp3 -t 1 -r 1.3 &");
	}
	if (w->oldfps != 0)
		mlx_string_put(w->mlx_ptr, w->win_ptr, 5, 5, 0xffffff,
		ft_itoa(w->oldfps));
}

int		raycaster(t_wolf *w)
{
	int	x;

	w->frame = clock();
	x = -1;
	while (++x < WWIN)
	{
		w->hit = 0;
		w->camerax = 2.0 * (double)x / (double)WWIN - 1.0;
		w->raydirx = w->dirx + w->planex * w->camerax;
		w->raydiry = w->diry + w->planey * w->camerax;
		w->mapx = (int)(w->posx);
		w->mapy = (int)(w->posy);
		w->deltadistx = fabs(1 / w->raydirx);
		w->deltadisty = fabs(1 / w->raydiry);
		sidecalc(w);
		findhit(w);
		drawline(w, x);
		drawfloor(w, x);
	}
	spritecaster(w);
	moving(w);
	fps(w);
	return (0);
}
