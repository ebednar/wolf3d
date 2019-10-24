/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getintmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <twitting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/27 16:17:18 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		getwidth(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] != ' ' && str[j] != '\0')
		{
			i++;
			while (str[j] != ' ' && str[j] != '\0')
				j++;
		}
		if (str[j] == '\0')
			break ;
		j++;
	}
	return (i);
}

int		getmapsize(int *height, int *width, char *filename)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error(3);
	while (get_next_line(fd, &line) > 0)
	{
		if (j < getwidth(line))
			j = getwidth(line);
		free(line);
		i++;
	}
	*height = i;
	*width = j;
	close(fd);
	if (i < 3 || j < 3)
		ft_error(3);
	return (1);
}

int		**mapmalloc(int **map, int heigth, int width)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!(map = (int **)malloc(sizeof(int *) * (heigth + 1))))
		ft_error(2);
	while (i < heigth)
	{
		if (!(map[i] = (int *)malloc(sizeof(int) * width)))
			ft_error(2);
		while (j < width)
			map[i][j++] = 0;
		i++;
	}
	map[i] = 0;
	return (map);
}

int		makemapstr(int counter, int *mapsize, int **map, char *line)
{
	int i;
	int	sprites;

	i = 0;
	sprites = 0;
	while (i < mapsize[1])
	{
		map[counter][i] = ft_atoi(line);
		if (map[counter][i] == 10)
			sprites++;
		while (*line != ' ' && *line != '\0')
			line++;
		while (*line == ' ')
			line++;
		i++;
	}
	return (sprites);
}

int		**getintmap(char *filename, t_wolf *w)
{
	int		**map;
	int		fd;
	char	*line;
	int		mapsize[2];
	int		counter;

	counter = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		ft_error(3);
	map = NULL;
	getmapsize(&(mapsize[0]), &(mapsize[1]), filename);
	map = mapmalloc(map, mapsize[0], mapsize[1]);
	while (get_next_line(fd, &line))
	{
		w->sprcount += makemapstr(counter, mapsize, map, line);
		free(line);
		counter++;
	}
	findsprites(w, mapsize, map);
	close(fd);
	return (map);
}
