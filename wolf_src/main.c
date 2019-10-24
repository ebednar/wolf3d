/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/27 15:57:20 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	textoimg(t_wolf *w)
{
	char	*str[14];
	int		i;

	i = -1;
	str[0] = TEX0;
	str[1] = TEX1;
	str[2] = TEX2;
	str[3] = TEX3;
	str[4] = TEX4;
	str[5] = TEX5;
	str[6] = TEX6;
	str[7] = TEX7;
	str[8] = SKY;
	str[9] = BAR;
	str[10] = BAR;
	str[11] = SW1;
	str[12] = SW2;
	str[13] = SW3;
	while (++i < 14)
	{
		w->teximg[i].img_ptr = mlx_xpm_file_to_image(w->mlx_ptr, str[i], \
				&w->teximg[i].txtwidth, &w->teximg[i].txtheight);
		w->teximg[i].data = (int *)mlx_get_data_addr(w->teximg[i].img_ptr, \
			&w->teximg[i].bpp, &w->teximg[i].size_l, &w->teximg[i].endian);
	}
}

void	ft_error(int errnum)
{
	if (errnum == 1)
		ft_putendl_fd("Usage: ./wolf3d [map name]", 2);
	if (errnum == 2)
		ft_putendl_fd("Memory allocation error, aborting...", 2);
	if (errnum == 3)
		ft_putendl_fd("Something wrong with map file, aborting...", 2);
	if (errnum == 4)
	{
		system("killall afplay");
		ft_putendl_fd("Position of player is invalid, aborting...", 2);
	}
	exit(errnum);
}

void	caster_init(t_wolf *w)
{
	int	i;
	int j;

	w->posx = 2;
	w->posy = 2;
	i = (int)w->posy;
	j = (int)w->posx;
	if ((w->map[i][j] != 0) || (w->map[i - 1][j - 1] != 0) ||
		(w->map[i - 1][j] != 0) || (w->map[i][j - 1] != 0))
		ft_error(4);
	w->dirx = -1;
	w->diry = 0;
	w->planex = 0;
	w->planey = 0.66;
	w->skyangle = 0;
	w->swing = 0;
}

void	wininit(t_wolf *wolf)
{
	wolf->mlx_ptr = mlx_init();
	wolf->win_ptr = mlx_new_window(wolf->mlx_ptr, WWIN, HWIN, "Wolfenstein 3D");
	wolf->img.img_ptr = mlx_new_image(wolf->mlx_ptr, WWIN, HWIN);
	wolf->img.data = (int *)mlx_get_data_addr(wolf->img.img_ptr,
	&wolf->img.bpp, &wolf->img.size_l, &wolf->img.endian);
	wolf->lefttoggler = 0;
	wolf->righttoggler = 0;
	wolf->uptoggler = 0;
	wolf->downtoggler = 0;
	wolf->fps = 0;
	wolf->oldfps = 0;
	wolf->timer = 0;
	textoimg(wolf);
	system("afplay sound/music.mp3 -v 0.1 &");
}

int		main(int argc, char **argv)
{
	t_wolf wolf;

	if (argc == 2)
	{
		wolf.sprcount = 0;
		if (!(wolf.map = getintmap(argv[1], &wolf)))
			return (1);
		wininit(&wolf);
		caster_init(&wolf);
	}
	else
		ft_error(1);
	mlx_loop_hook(wolf.mlx_ptr, raycaster, &wolf);
	mlx_hook(wolf.win_ptr, 2, 1L << 0, key_press, &wolf);
	mlx_hook(wolf.win_ptr, 3, 1L << 0, key_release, &wolf);
	mlx_hook(wolf.win_ptr, 17, 1L << 17, crossclose, &wolf);
	mlx_loop(wolf.mlx_ptr);
	return (0);
}
