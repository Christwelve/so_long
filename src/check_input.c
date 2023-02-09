/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 14:04:41 by cmeng             #+#    #+#             */
/*   Updated: 2023/02/09 12:50:29 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	ft_valid_map(t_map *map);
static int	ft_check_characters(t_map *map);
static int	ft_check_borders(t_map *map);

// return(1) = invalid map
// 	1) check retangularity (line 40)
// 	2) get map size (map->width // map->height)
// 	3) string in map->map
//  4) check p,c,e

int	ft_check_map(t_map *map, int fd)
{
	char	*tmp;
	int		x;

	x = -1;
	map->height = 0;
	if (ft_calloc2(1, 1, (void *) &map->map))
		return (1);
	while (x != 0)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		map->width = ft_strlen(tmp);
		if (tmp[map->width - 1] == '\n')
			map->width--;
		if (map->width == 0)
			return (free(map->map), free(tmp), 1);
		if (x != -1 && map->width != x)
			return (free(map->map), free(tmp), 1);
		x = map->width;
		if (ft_strjoin_compact(&map->map, tmp))
			return (free(map->map), free(tmp), 1);
		map->height++;
	}
	if (ft_valid_map(map))
		return (free(map->map), free(tmp), 1);
	return (free(tmp), 0);
}

static int	ft_valid_map(t_map *map)
{
	int	i;
	int	e;
	int	p;
	int	n;

	i = 0;
	e = 0;
	p = 0;
	map->score = 0;
	n = ft_strlen(map->map);
	while (i++ < n)
	{
		if (map->map[i] == 'C')
			map->score++;
		else if (map->map[i] == 'E')
			e++;
		else if (map->map[i] == 'P')
			p++;
	}
	if (map->score && p == 1 && e == 1 && \
		!ft_check_borders(map) && !ft_check_characters(map))
		return (0);
	else
		return (1);
}

static int	ft_check_characters(t_map *map)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(map->map);
	while (i < n)
	{
		if (map->map[i] != '0' && map->map[i] != '1' && map->map[i] != 'C'
			&& map->map[i] != 'E' && map->map[i] != 'P')
			return (1);
		if (map->map[i] == 'P')
			map->pos_player = i;
		if (map->map[i] == 'E')
			map->pos_exit = i;
		i++;
	}
	return (0);
}

// return(0) = valid
// return(1) = invalid
// if() y0/x0/ymax/xmax
static int	ft_check_borders(t_map *map)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(map->map);
	while (i < n)
	{
		if (i / map->width == 0)
			if (!(map->map[i] == '1'))
				return (1);
		if (i % map->width == 0)
			if (!(map->map[i] == '1'))
				return (1);
		if (i >= map->width * (map->height - 1))
			if (!(map->map[i] == '1'))
				return (1);
		if (i % map->width == map->width - 1)
			if (!(map->map[i] == '1'))
				return (1);
		i++;
	}
	return (0);
}
