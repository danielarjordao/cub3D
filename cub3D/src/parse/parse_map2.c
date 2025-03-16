/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:27:03 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/16 16:19:42 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_add_space_end(char *line, int width)
{
	char	*new_line;
	int		i;

	i = 0;
	new_line = ft_calloc(1, width + 1);
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

bool	check_borders_line(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < map->map_width)
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
	if (map->map[y][*x - 1] != '1' && !map->map[y][*x])
		return (msg_error(MAP_BORDER_ERR));
	else if (map->map[y][*x] && (map->map[y][(*x) - 1] == '0'
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
		while (y < map->map_height)
		{
			while (map->map[y] && ft_isspace(map->map[y][x]))
				y++;
			if (!map->map[y])
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
	if (map->map[*y] && map->map[*y][x] && map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	else if ((*y) < map->map_height)
		(*y)++;
	while (map->map[*y] && (*y) < map->map_height &&
		(map->map[*y][x] == '0' || map->map[*y][x] == 'N'
		|| map->map[*y][x] == 'S' || map->map[*y][x] == 'E'
		|| map->map[*y][x] == 'W'))
		(*y)++;
	if ((*y) == map->map_height && map->map[*y - 1][x] != '1' && !ft_isspace(map->map[(*y) - 1][x]))
		return (msg_error(MAP_BORDER_ERR));
	else if (map->map[*y] && (map->map[(*y) - 1][x] == '0'
		|| map->map[(*y) - 1][x] == 'N' || map->map[(*y) - 1][x] == 'S'
		|| map->map[(*y) - 1][x] == 'E' || map->map[(*y) - 1][x] == 'W')
		&& map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	return (true);
}
