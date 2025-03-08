#include "../../includes/cub3d.h"

bool	is_a_texture(char *line)
{
	line += ignore_spaces(line);
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		&& ft_isspace(line[2]))
		return (true);
	else
		return (false);
}
bool	is_texture_valid(char *line, t_map **map)
{
	int		fd;
	char	*path;
	char	c;

	line += ignore_spaces(line);
	c = *line;
	line += 2;
	path = ft_trim_spaces(line);
	if (!path)
		return (msg_error(MISSING_INFO));
	if (!is_valid_extension(path, ".xpm"))
	{
		free(path);
		return (msg_error(TEX_INVALID_EXT));
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		return (msg_error(TEX_OPEN_FAIL));
	}
	close(fd);
	if (!add_texture(path, c, map))
		return (false);
	return (true);
}

bool	add_texture(char *path, char c, t_map **map)
{
	(void)map;
	if (c == 'N' && !(*map)->no_texture)
		(*map)->no_texture = path;
	else if (c == 'S' && !(*map)->so_texture)
		(*map)->so_texture = path;
	else if (c == 'W' && !(*map)->we_texture)
		(*map)->we_texture = path;
	else if (c == 'E' && !(*map)->ea_texture)
		(*map)->ea_texture = path;
	else
	{
		free(path);
		return (msg_error(TEX_PATH_DUP));
	}
	return (true);
}
