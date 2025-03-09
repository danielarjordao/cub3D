/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:26:56 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/09 16:26:57 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
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
		(*map)->map = ft_realloc((*map)->map, i * sizeof(char *),
				(i + 2) * sizeof(char *));
		(*map)->map[i] = ft_strdup(line);
		(*map)->map[i + 1] = NULL;
		if ((int)ft_strlen(line) > (*map)->map_width)
			(*map)->map_width = ft_strlen(line);
	}
	(*map)->map_height++;
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

void	add_space_to_map(t_map *map)
{
	int		i;
	char	*new_line;

	i = 0;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) != (size_t)map->map_width)
		{
			new_line = ft_calloc(1, sizeof(char) * map->map_width + 1);
			if (!new_line)
				return ;
			new_line = ft_add_space_end(map, new_line, i);
			free(map->map[i]);
			map->map[i] = new_line;
		}
		i++;
	}
}
