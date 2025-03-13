/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:27:03 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/13 18:44:31 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_add_space_end(t_map *map, char *new_line, int i)
{
	int	j;

	j = 0;
	printf("map->map[%d] = %s\n", i, map->map[i]);
	while (j < map->map_width)
	{
		if (map->map[i][j] && map->map[i][j] != '\n')
			new_line[j] = map->map[i][j];
		else
			new_line[j] = ' ';
		j++;
	}
	new_line[j] = '\n';
	new_line[j++] = '\0';
	printf("new_line = %s\n", new_line);
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
	{
		printf("map->map_width = %d\n", map->map_width);
		printf("map->map_height = %d\n", map->map_height);
		printf("map->map[%d][%d] = %c\n", y, *x, map->map[y][*x]);
		printf("exit first if line\n");
		return (msg_error(MAP_BORDER_ERR));
	}
	else
		(*x)++;
	while (map->map[y][*x] && (map->map[y][*x] == '0' || map->map[y][*x] == 'N'
		|| map->map[y][*x] == 'S' || map->map[y][*x] == 'E'
		|| map->map[y][*x] == 'W'))
		(*x)++;
	if (map->map[y][*x - 1] != '1' && !map->map[y][*x])
	{
		printf("exit second if line\n");
		return (msg_error(MAP_BORDER_ERR));
	}
	else if (map->map[y][*x] && (map->map[y][(*x) - 1] == '0'
		|| map->map[y][(*x) - 1] == 'N' || map->map[y][(*x) - 1] == 'S'
		|| map->map[y][(*x) - 1] == 'E' || map->map[y][(*x) - 1] == 'W')
		&& map->map[y][*x] != '1')
	{
		printf("exit else if line\n");
		return (msg_error(MAP_BORDER_ERR));
	}
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
	{
		printf("exit first if");
		return (msg_error(MAP_BORDER_ERR));
	}
	else if ((*y) < map->map_height)
		(*y)++;
	while (map->map[*y] && (*y) < map->map_height &&
		(map->map[*y][x] == '0' || map->map[*y][x] == 'N'
		|| map->map[*y][x] == 'S' || map->map[*y][x] == 'E'
		|| map->map[*y][x] == 'W'))
		(*y)++;
	if ((*y) == map->map_height && map->map[*y - 1][x] != '1' && !ft_isspace(map->map[(*y) - 1][x]))
	{
		printf("height = %d\n", map->map_height);
		printf("map->map[*%d][%d] = '%c'\n", (*y) - 1, x, map->map[(*y) - 1][x]);
		printf("exit second if");
		return (msg_error(MAP_BORDER_ERR));
	}
	else if (map->map[*y] && (map->map[(*y) - 1][x] == '0'
		|| map->map[(*y) - 1][x] == 'N' || map->map[(*y) - 1][x] == 'S'
		|| map->map[(*y) - 1][x] == 'E' || map->map[(*y) - 1][x] == 'W')
		&& map->map[*y][x] != '1')
	{
		printf("exit else if");
		return (msg_error(MAP_BORDER_ERR));
	}
	printf("map->map[*%d - 1][%d] = %c\n", (*y) - 1, x, map->map[(*y) - 1][x]);
	return (true);
}
