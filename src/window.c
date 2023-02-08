/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 15:20:42 by cmeng             #+#    #+#             */
/*   Updated: 2023/02/08 09:54:21 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	ft_draw_textures(t_map *map);
static int	ft_create_textures(t_map *map);
static int	ft_draw_borders(t_map *map, int32_t i);
static int	set_image_to_window(t_map *map);

int	ft_create_window(t_map *map)
{
	int32_t	width;
	int32_t	height;

	map->moves = 0;
	width = map->width * PIXELS;
	height = map->height * PIXELS;
	map->window = mlx_init(width, height, "10_rules_of_42", true);
	if (!map->window)
		exit(EXIT_FAILURE);
	mlx_set_window_limit(map->window, width, height, width, height);
	ft_create_textures(map);
	map->bg_img = mlx_new_image(map->window, width, height);
	map->collect_img = mlx_new_image(map->window, width, height);
	map->player_img = mlx_new_image(map->window, width, height);
	ft_draw_textures(map);
	set_image_to_window(map);
	ft_printf("\n\n%s\n", "\033[32mWelcome to 10 rules of 42 Heilbronn!");
	ft_printf("%s", "\033[37mHelp little Ole collect all the rules");
	ft_printf("%s\n\n\n", " and find the exit in cluster 1!");
	return (0);
}

static int	ft_create_textures(t_map *map)
{
	map->pc = mlx_load_png("graphics/pc.png");
	map->pc_left = mlx_load_png("graphics/pc_left.png");
	map->pc_down = mlx_load_png("graphics/pc_down.png");
	map->pc_right = mlx_load_png("graphics/pc_right.png");
	map->floor = mlx_load_png("graphics/new_floor.png");
	map->paper = mlx_load_png("graphics/rule.png");
	map->exit = mlx_load_png("graphics/bh.png");
	map->player_down = mlx_load_png("graphics/b_player_down.png");
	return (0);
}

static int	ft_draw_textures(t_map *map)
{
	size_t	i;
	int32_t	x;
	int32_t	y;

	i = 0;
	x = 0;
	while (i < ft_strlen(map->map))
	{
		x = (i % map->width) * PIXELS;
		y = (i / map->width) * PIXELS;
		if (map->map[i] == '1')
			ft_draw_borders(map, i);
		else if (map->map[i] == 'C')
			mlx_draw_texture(map->collect_img, map->paper, x, y);
		else
			mlx_draw_texture(map->bg_img, map->floor, x, y);
		if (map->map[i] == 'P')
			mlx_draw_texture(map->player_img, map->player_down, x, y);
		i++;
	}
	return (0);
}

static int	ft_draw_borders(t_map *map, int32_t i)
{
	int32_t	x;
	int32_t	y;

	x = (i % map->width) * PIXELS;
	y = (i / map->width) * PIXELS;
	if (i / map->width == 0)
		mlx_draw_texture(map->bg_img, map->pc, x, y);
	else if (i / map->width == map->height - 1)
		mlx_draw_texture(map->bg_img, map->pc_down, x, y);
	else if (i % map->width == 0)
		mlx_draw_texture(map->bg_img, map->pc_left, x, y);
	else if (i % map->width == map->width - 1)
		mlx_draw_texture(map->bg_img, map->pc_right, x, y);
	else
		mlx_draw_texture(map->bg_img, map->pc, x, y);
	return (0);
}

static int	set_image_to_window(t_map *map)
{
	mlx_image_to_window(map->window, map->bg_img, 0, 0);
	mlx_set_instance_depth(map->bg_img->instances, 0);
	mlx_image_to_window(map->window, map->collect_img, 0, 0);
	mlx_set_instance_depth(map->collect_img->instances, 1);
	mlx_image_to_window(map->window, map->player_img, 0, 0);
	mlx_set_instance_depth(map->player_img->instances, 3);
	return (0);
}
