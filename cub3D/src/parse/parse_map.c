#include "../../includes/cub3d.h"

bool	is_map_valid(char *line, t_map **map)
{
	int	i;

	i = 0;
	if (!are_colors_and_textures_set(map))
		return (msg_error(MISSING_INFO));
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && !ft_isspace(line[i]))
		{
			return (msg_error(MAP_INVALID_CHAR));
		}
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if ((*map)->player_dir)
				return (msg_error(MAP_PLAYER_DUP));
			(*map)->player_dir = line[i];
			(*map)->player_x = i + 1;
			(*map)->player_y = (*map)->map_height + 1;
		}
		i++;
	}
	add_map_line(line, map);
	return (true);
}

bool	are_colors_and_textures_set(t_map **map)
{
	if (!(*map)->no_texture || !(*map)->so_texture || !(*map)->we_texture
		|| !(*map)->ea_texture || (*map)->floor_color[0] == -1
		|| (*map)->ceiling_color[0] == -1)
		return (false);
	return (true);
}

void	add_map_line(char *line, t_map **map)
{
	int		i;

	i = 0;
	if (!(*map)->map)
	{
		(*map)->map = ft_calloc(1, sizeof(char *) * 2);
		(*map)->map[0] = ft_strdup(line);
		(*map)->map[1] = NULL;
		(*map)->map_width = ft_strlen(line);
	}
	else
	{
		while ((*map)->map[i])
			i++;
		(*map)->map = ft_realloc((*map)->map, i * sizeof(char *), (i + 2) * sizeof(char *));
		(*map)->map[i] = ft_strdup(line);
		(*map)->map[i + 1] = NULL;
		if ((int)ft_strlen(line) > (*map)->map_width)
			(*map)->map_width = ft_strlen(line);
	}
	(*map)->map_height++;
}

// testar flood fill para verificar se o mapa é válido
// verificar se o mapa é fechado

/*
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
	while (map->map[y][*x] == '0' || map->map[y][*x] == 'N' || map->map[y][*x] == 'S'
		|| map->map[y][*x] == 'E' || map->map[y][*x] == 'W')
		(*x)++;
	if ((map->map[y][(*x) - 1] == '0' || map->map[y][(*x) - 1] == 'N' || map->map[y][(*x) - 1] == 'S'
		|| map->map[y][(*x) - 1] == 'E' || map->map[y][(*x) - 1] == 'W') && map->map[y][*x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	return (true);
}

bool	check_borders_column(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->map[y])
	{
		y = 0;
		while (map->map[y] && map->map[y][x] && map->map[y][x] != '\n')
		{
			while (map->map[y][x] && ft_isspace(map->map[y][x]))
				y++;
			if (!map->map[y][x] || map->map[y][x] == '\n')
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
	if (map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	else
		(*y)++;
	while (map->map[*y] && (map->map[*y][x] == '0' || map->map[*y][x] == 'N' || map->map[*y][x] == 'S'
		|| map->map[*y][x] == 'E' || map->map[*y][x] == 'W'))
		(*y)++;
	if (map->map[*y] && ((map->map[*y - 1][x] == '0' || map->map[*y - 1][x] == 'N' || map->map[*y - 1][x] == 'S'
		|| map->map[*y - 1][x] == 'E' || map->map[*y - 1][x] == 'W')) && map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	if (map->map[*y] && map->map[*y][x])
		printf("map->map[%d][%d]: %c\n", *y, x, map->map[*y][x]);
	if (map->map[*y] && map->map[*y - 1][x])
		printf("map->map[%d - 1][%d]: %c\n", *y - 1, x, map->map[*y - 1][x]);
	return (true);
}*/
