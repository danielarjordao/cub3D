/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:27:03 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/09 16:27:04 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_borders(t_map *map)
{
	if (!check_borders_line(map))
		return (false);
	if (!check_borders_column(map))
		return (false);
	return (true);
}

bool	check_borders_line(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			while (ft_isspace(map->map[y][x]))
				x++;
			if (!map->map[y][x] || map->map[y][x] == '\n')
				break ;
			else if (!check_line(map, &x, y))
				return (false);
		}
		y++;
	}
	return (true);
}

bool	check_line(t_map *map, int *x, int y)
{
	if (map->map[y][*x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	else
		(*x)++;
	while (map->map[y][*x] && (map->map[y][*x] == '0' || map->map[y][*x] == 'N'
		|| map->map[y][*x] == 'S' || map->map[y][*x] == 'E'
		|| map->map[y][*x] == 'W'))
		(*x)++;
	if (map->map[y][*x] && (map->map[y][(*x) - 1] == '0'
		|| map->map[y][(*x) - 1] == 'N' || map->map[y][(*x) - 1] == 'S'
		|| map->map[y][(*x) - 1] == 'E' || map->map[y][(*x) - 1] == 'W')
		&& map->map[y][*x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	return (true);
}

bool	check_borders_column(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (x < map->map_width)
	{
		y = 0;
		while (y < map->map_height && (int)ft_strlen(map->map[y]) > x)
		{
			while (map->map[y] && x < (int)ft_strlen(map->map[y])
				&& ft_isspace(map->map[y][x]))
				y++;
			if (!map->map[y] || x >= (int)ft_strlen(map->map[y]))
				break ;
			else if (!check_column(map, x, &y))
				return (false);
		}
		x++;
	}
	return (true);
}

bool	check_column(t_map *map, int x, int *y)
{
	if (map->map[*y] && x < (int)ft_strlen(map->map[*y])
		&& map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	else if (*y < map->map_height)
		(*y)++;
	while (map->map[*y] && x < (int)ft_strlen(map->map[*y])
		&& (map->map[*y][x] == '0' || map->map[*y][x] == 'N'
		|| map->map[*y][x] == 'S' || map->map[*y][x] == 'E'
		|| map->map[*y][x] == 'W'))
		(*y)++;
	if (map->map[*y] && x < (int)ft_strlen(map->map[*y])
		&& ((map->map[*y - 1][x] == '0' || map->map[*y - 1][x] == 'N'
		|| map->map[*y - 1][x] == 'S' || map->map[*y - 1][x] == 'E'
		|| map->map[*y - 1][x] == 'W')) && map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	return (true);
}
