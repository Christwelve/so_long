/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:14:31 by cmeng             #+#    #+#             */
/*   Updated: 2023/02/07 17:06:14 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int		process_move(t_map *map, int index);
static int		ft_check_cell(int direct, t_map *map);
static char		ft_10_rules(t_map *map);
static int		ft_monitor(t_map *map);

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	if (keydata.action != MLX_PRESS)
		return ;
	map = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(map->window);
	if (keydata.key == MLX_KEY_W)
	{
		if (map->monitor_img)
			mlx_delete_image(map->window, map->monitor_img);
		if (!process_move(map, map->pos_player - map->width))
			ft_check_cell(1, map);
	}
	if (keydata.key == MLX_KEY_S)
		if (!process_move(map, map->pos_player + map->width))
			ft_check_cell(2, map);
	if (keydata.key == MLX_KEY_A)
		if (!process_move(map, map->pos_player - 1))
			ft_check_cell(3, map);
	if (keydata.key == MLX_KEY_D)
		if (!process_move(map, map->pos_player + 1))
			ft_check_cell(4, map);
	if (map->pos_player == map->pos_exit)
		mlx_close_window(map->window);
}

int	process_move(t_map *map, int index)
{
	const char	cell = map->map[index];
	int32_t		x;
	int32_t		y;
	int32_t		xe;
	int32_t		ye;

	x = (index % map->width) * PIXELS;
	y = (index / map->width) * PIXELS;
	xe = (map->pos_exit % map->width) * PIXELS;
	ye = (map->pos_exit / map->width) * PIXELS;
	if (cell == '1')
		return (1);
	if (cell == 'C')
	{
		map->map[index] = '0';
		mlx_draw_texture(map->collect_img, map->floor, x, y);
		map->score--;
		ft_10_rules(map);
	}
	if (cell == 'E')
		if (map->score != 0)
			return (1);
	if (map->score == 0)
		mlx_draw_texture(map->bg_img, map->exit, xe, ye);
	return (0);
}

// direct:
// 1=up / 2=down / 3=left /4=right
static int	ft_check_cell(int direct, t_map *map)
{
	if (direct == 1)
	{
		map->player_img->instances[0].y -= PIXELS;
		map->pos_player -= map->width;
	}
	if (direct == 2)
	{
		map->player_img->instances[0].y += PIXELS;
		map->pos_player += map->width;
	}
	if (direct == 3)
	{
		map->player_img->instances[0].x -= PIXELS;
		map->pos_player -= 1;
	}
	if (direct == 4)
	{
		map->player_img->instances[0].x += PIXELS;
		map->pos_player += 1;
	}
	ft_printf("%i\n", ++map->moves);
	return (0);
}

char	ft_10_rules(t_map *map)
{
	if (map->score < 10)
	{
		ft_printf("\n%s%i", "\033[32mCollected rule no.", map->score);
		ft_printf("%s\n\n", "\033[37m");
	}
	if (map->score == 0)
	{
		ft_printf("\n\n%s\n\n", "\033[32mYou've collected all the rules!\033[37m\n");
		if (map->width >= 20 && map->height >= 10)
			ft_monitor(map);
		ft_printf("%s", "\033[31mUnfortunatly you broke rule no.4 by playing");
		ft_printf("%s\n", " this so_long game!");
		ft_printf("%s", "Getting absorbed by the blackhole is the only");
		ft_printf("%s\n\n\n", " solution for such a rude behavior!\033[37m");
	}
	return (0);
}

static int	ft_monitor(t_map *map)
{
	int32_t	width;
	int32_t	height;

	width = map->width * PIXELS;
	height = map->height * PIXELS;
	map->monitor = mlx_load_png("graphics/green.png");
	map->monitor_img = mlx_new_image(map->window, width, height);
	mlx_draw_texture(map->monitor_img, map->monitor, 0, 0);
	mlx_image_to_window(map->window, map->monitor_img, 0, 0);
	mlx_set_instance_depth(map->player_img->instances, 2);
	return (0);
}
