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

void	add_space_to_map(t_map *map)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) != (size_t)map->map_width)
		{
			j = 0;
			new_line = ft_calloc(1, sizeof(char) * map->map_width + 1);
			if (!new_line)
				return ;
			while (j < (int)ft_strlen(map->map[i]))
			{
				if (map->map[i][j])
					new_line[j] = map->map[i][j];
				else
					new_line[j] = ' ';
				j++;
			}
			new_line[j - 1] = '\n';
			new_line[j] = '\0';
			free(map->map[i]);
			map->map[i] = new_line;
		}
		i++;
	}
}

bool	are_there_only_walls(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x]== '0' || map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_empty_lines_in_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (is_empty_line(map->map[i]))
		{
			while (is_empty_line(map->map[i]))
				i++;
			if (!map->map[i])
				return (false);
			else
				return (true);
		}
		i++;
	}
	return (false);
}

bool	check_content(t_map *map)
{
	if (check_empty_lines_in_map(map))
		return (msg_error(MAP_FORMAT_ERR));
	if (!map->player_dir)
		return (msg_error(MAP_NO_PLAYER));
	add_space_to_map(map);
	if (!check_borders(map))
		return (false);
	return (true);
}

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
	while (map->map[y][*x] && (map->map[y][*x] == '0' || map->map[y][*x] == 'N' || map->map[y][*x] == 'S'
		|| map->map[y][*x] == 'E' || map->map[y][*x] == 'W'))
		(*x)++;
	if (map->map[y][*x] && (map->map[y][(*x) - 1] == '0' || map->map[y][(*x) - 1] == 'N' || map->map[y][(*x) - 1] == 'S'
		|| map->map[y][(*x) - 1] == 'E' || map->map[y][(*x) - 1] == 'W') && map->map[y][*x] != '1')
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
			while (map->map[y] && x < (int)ft_strlen(map->map[y]) && ft_isspace(map->map[y][x]))
				y++;
			if (!map->map[y] || x >= (int)ft_strlen(map->map[y]))
				break;
			else if (!check_column(map, x, &y))
				return (false);
		}
		x++;
	}
	return (true);
}

bool	check_column(t_map *map, int x, int *y)
{
	if (map->map[*y] && x < (int)ft_strlen(map->map[*y]) && map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	else if (*y < map->map_height)
		(*y)++;
	while (map->map[*y] && x < (int)ft_strlen(map->map[*y]) && (map->map[*y][x] == '0' || map->map[*y][x] == 'N' || map->map[*y][x] == 'S'
		|| map->map[*y][x] == 'E' || map->map[*y][x] == 'W'))
		(*y)++;
	if (map->map[*y] && x < (int)ft_strlen(map->map[*y]) && ((map->map[*y - 1][x] == '0' || map->map[*y - 1][x] == 'N' || map->map[*y - 1][x] == 'S'
		|| map->map[*y - 1][x] == 'E' || map->map[*y - 1][x] == 'W')) && map->map[*y][x] != '1')
		return (msg_error(MAP_BORDER_ERR));
	return (true);
}
