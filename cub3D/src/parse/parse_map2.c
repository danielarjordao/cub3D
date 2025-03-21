/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniela <daniela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:27:03 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/21 17:46:14 by daniela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	check_empty_lines_in_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		if (is_empty_line(map->map[i]))
		{
			j = i;
			while (map->map[i] && is_empty_line(map->map[i]))
				i++;
			if (!map->map[i])
			{
				clean_extra_empty_lines(map, j);
				return (false);
			}
			else if (check_null_line(map, i, j))
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_borders(t_map *map)
{
	int		x;
	int		y;
	char	**temp_map;

	y = 0;
	temp_map = copy_map(map);
	while (temp_map[y])
	{
		x = 0;
		while (temp_map[y][x])
		{
			if (ft_strrchr("0NSWE", temp_map[y][x]))
			{
				if (!recursively_check_borders(map, temp_map, x, y))
				{
					ft_free_matrix(temp_map);
					return (false);
				}
			}
			x++;
		}
		y++;
	}
	ft_free_matrix(temp_map);
	return (true);
}

char	**copy_map(t_map *map)
{
	char	**temp_map;
	int		i;

	i = 0;
	temp_map = ft_calloc(map->map_height + 1, sizeof(char *));
	while (map->map[i])
	{
		temp_map[i] = ft_strdup(map->map[i]);
		i++;
	}
	return (temp_map);
}

bool	recursively_check_borders(t_map *map, char **temp_map, int x, int y)
{
	if (x < 0 || y < 0 || x >= map->map_width || y >= map->map_height)
		return (false);
	if (temp_map[y][x] == ' ')
		return (false);
	if (temp_map[y][x] == '1')
		return (true);
	temp_map[y][x] = '1';
	if (!recursively_check_borders(map, temp_map, x + 1, y)
		|| !recursively_check_borders(map, temp_map, x - 1, y)
		|| !recursively_check_borders(map, temp_map, x, y + 1)
		|| !recursively_check_borders(map, temp_map, x, y - 1))
		return (false);
	return (true);
}
