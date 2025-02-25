#include "../../includes/cub3d.h"

bool	is_color_valid(char *line, t_map **map)
{
	int	i;

	i = ignore_spaces(line);
	if (line[i] == 'F')
		return (add_color(line + i + 1, 'F', map));
	else if (line[i] == 'C')
		return (add_color(line + i + 1, 'C', map));
	else
		return (false);
}

bool	add_color(char *line, char c, t_map **map)
{
	char	*temp;
	int		*color;
	int		i;

	if (c == 'C')
		color = (*map)->ceiling_color;
	else
		color = (*map)->floor_color;
	i = 0;
	while (i < 3)
	{
		line += ignore_spaces(line);
		if (color[i] != -1)
			return (msg_error(COL_DUPLICATE));
		temp = ft_substr(line, 0, 3);
		color[i] = ft_atoi(line);
		if (color[i] < 0 || color[i] > 255)
			return (msg_error(COL_FORMAT_ERR));
		line += ft_strlen(temp) + 1;
		i++;
		free(temp);
	}
	line += ignore_spaces(line);
	if (*line)
		return (msg_error(COL_FORMAT_ERR));
	return (true);
}
