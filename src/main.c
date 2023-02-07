/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:29:23 by cmeng             #+#    #+#             */
/*   Updated: 2023/02/07 17:48:36 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	ft_check_file_type(char *file);
static int	ft_check_flood(t_map *map);
static void	ft_flood(int pos, int width, char *map, t_flood *flood);

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc != 2)
		return (1);
	if (ft_check_file_type(argv[1]))
		return (ft_printf("%s\n", "\033[31mError:\033[37m Invalid map extension"));
	fd = open(argv[1], O_RDONLY);
	if (ft_check_map(&map, fd))
		return (ft_printf("%s\n", "\033[31mError:\033[37m Invalid map"));
	if (map.width > 30 || map.height > 20)
		return (ft_printf("%s\n", "\033[31mError:\033[37m Map is too big"));
	if (ft_check_flood(&map))
		return (ft_printf("%s\n", "\033[31mError:\033[37m C or E not reachable"));
	ft_create_window(&map);
	return (0);
}

static int	ft_check_file_type(char *file)
{
	const char	*ending = ".ber";
	int			ie;
	int			i;

	i = ft_strlen(file) - 1;
	ie = ft_strlen(ending) - 1;
	while (ie >= 0)
	{
		if (file[i--] != ending[ie--])
			return (1);
	}
	return (0);
}

static int	ft_check_flood(t_map *map)
{
	int		pos;
	char	*map_dup;
	t_flood	flood;

	pos = map->pos_player;
	flood.collect = 0;
	flood.exit = 0;
	map_dup = ft_strdup(map->map);
	ft_flood(pos, map->width, map_dup, &flood);
	if (flood.collect != map->score)
		return (1);
	if (flood.exit != 1)
		return (1);
	return (0);
}

static void	ft_flood(int pos, int width, char *map, t_flood *flood)
{
	if (map[pos] == '1')
		return ;
	if (map[pos] == 'E')
		flood->exit = 1;
	if (map[pos] == 'C')
		flood->collect++;
	map[pos] = '1';
	ft_flood(pos - width, width, map, flood);
	ft_flood(pos + 1, width, map, flood);
	ft_flood(pos - 1, width, map, flood);
	ft_flood(pos + width, width, map, flood);
}
