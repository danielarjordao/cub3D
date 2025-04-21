/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:56:22 by dramos-j          #+#    #+#             */
/*   Updated: 2025/04/21 19:33:57 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	parse(char *file, t_map **map)
{
	int	fd;

	if (!is_valid_extension(file, ".cub"))
		return (msg_error(INVALID_EXT));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (msg_error(OPEN_FAIL));
	if (!init_map(map) || !is_content_valid(fd, map) || !check_content(*map))
	{
		free_map(*map);
		return (false);
	}
	return (true);
}

bool	is_valid_extension(char *file, char *ext)
{
	int	len;

	len = ft_strlen(file);
	file += len - 4;
	if (!file || ft_strncmp(file, ext, 4) != 0)
		return (false);
	return (true);
}

bool	is_content_valid(int fd, t_map **map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (msg_error(MISSING_INFO));
	while (line)
	{
		if (!is_line_valid(line, map))
		{
			free(line);
			close(fd);
			get_next_line(-1);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (true);
}

bool	is_line_valid(char *line, t_map **map)
{
	if (is_empty_line(line) && !(*map)->map)
		return (true);
	else if (is_a_texture(line))
		return (is_texture_valid(line, map));
	else if (is_a_color(line))
		return (is_color_valid(line, map));
	else if (is_map_valid(line, map))
		return (true);
	else
		return (false);
	return (true);
}

bool	check_content(t_map *map)
{
	if (!map->map)
		return (msg_error(MISSING_INFO));
	if (check_empty_lines_in_map(map))
		return (msg_error(MAP_FORMAT_ERR));
	if (!map->player_dir)
		return (msg_error(MAP_NO_PLAYER));
	if (!check_borders(map))
		return (msg_error(MAP_BORDER_ERR));
	return (true);
}
