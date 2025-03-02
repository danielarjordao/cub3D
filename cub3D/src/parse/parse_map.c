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
				return (msg_error(MAP_INVALID_CHAR));
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
