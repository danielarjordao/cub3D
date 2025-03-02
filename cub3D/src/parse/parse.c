#include "../../includes/cub3d.h"

bool	parse(char *file, t_map **map)
{
	int	fd;

	if (!is_valid_extension(file, ".cub"))
		return (msg_error(INVALID_EXT));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (msg_error(OPEN_FAIL));
	if (!init_map(map) || !is_content_valid(fd, map))
	{
		free_map(*map);
		return (false);
	}
	print_map(*map);
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
	(void)map;
	if (is_empty_line(line))
	{
		if (map && (*map)->map)
			return (msg_error(MAP_FORMAT_ERR));
		else
			return (true);
	}
	else if (is_texture_valid(line, map))
		return (true);
	else if (is_color_valid(line, map))
		return (true);
	else if (is_map_valid(line, map))
		return (true);
	else
		return (false);
}
