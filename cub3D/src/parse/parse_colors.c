#include "../../includes/cub3d.h"

bool	is_color_valid(char *line, t_map **map)
{
	int	i;

	i = ignore_spaces(line);
	if (line[i] == 'F')
		add_color(line + i + 1, 'F', map);
	else if (line[i] == 'C')
		add_color(line + i + 1, 'C', map);
	else
		return (false);
	return (true);
}

void	add_color(char *line, char c, t_map **map)
{
	(void)map;
	line += ignore_spaces(line);
	ft_printf(1, "Color %c: %s\n", c, line);
}
