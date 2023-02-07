/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:12:58 by cmeng             #+#    #+#             */
/*   Updated: 2023/02/07 16:21:32 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libs/libs.h"
# include "../MLX42/include/MLX42/MLX42.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define PIXELS 64

typedef struct s_map
{
	char			*map;
	mlx_t			*window;
	mlx_image_t		*bg_img;
	mlx_image_t		*collect_img;
	mlx_image_t		*player_img;
	mlx_image_t		*monitor_img;
	int				steps;
	int				score;
	int				moves;
	mlx_texture_t	*pc;
	mlx_texture_t	*pc_left;
	mlx_texture_t	*pc_down;
	mlx_texture_t	*pc_right;
	mlx_texture_t	*floor;
	mlx_texture_t	*paper;
	mlx_texture_t	*exit;
	mlx_texture_t	*player_down;
	mlx_texture_t	*monitor;
	int				height;
	int				width;
	int				pos_player;
	int				pos_exit;
}	t_map;

typedef struct s_flood
{
	int				collect;
	int				exit;
}	t_flood;

int			ft_create_window(t_map *map);
int			ft_check_map(t_map *map, int fd);
void		my_keyhook(mlx_key_data_t keydata, void *param);

#endif