#include "../../includes/cub3d.h"

bool	is_color_valid(char *line, t_map **map)
{
	char	**temp;
	char	c;

	line += ignore_spaces(line);
	if (*line != 'F' && *line != 'C')
		return (false);
	else
		c = *line;
	line++;
	temp = ft_split(line, ',');
	if (!temp || !temp[0] || !temp[1] || !temp[2] || temp[3])
	{
		ft_free_matrix(temp);
		return (msg_error(COL_FORMAT_ERR));
	}
	if (c == 'F')
		return (add_color(temp, (*map)->floor_color, map));
	else if (c == 'C')
		return (add_color(temp, (*map)->ceiling_color, map));
	else
		return (false);
}

bool	add_color(char **temp, int *color, t_map **map)
{
	int		i;

	i = 0;
	while (temp[i])
	{
		if (color[i] != -1)
		{
			ft_free_matrix(temp);
			return (msg_error(COL_DUPLICATE));
		}
		color[i] = ft_atoi(temp[i]);
		if (!valid_number_format(temp[i]) || color[i] < 0 || color[i] > 255)
		{
			ft_free_matrix(temp);
			return (msg_error(COL_FORMAT_ERR));
		}
		i++;
	}
	convert_rgb_to_hex(color, map);
	ft_free_matrix(temp);
	return (true);
}

bool	valid_number_format(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	while (str[i] && (ft_isdigit(str[i])))
		i++;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

void	convert_rgb_to_hex(int *color, t_map **map)
{
	if (color == (*map)->floor_color)
		(*map)->floor_color_hex = (color[0] << 16)
		+ (color[1] << 8) + color[2];
	else if (color == (*map)->ceiling_color)
		(*map)->ceiling_color_hex = (color[0] << 16)
		+ (color[1] << 8) + color[2];
}
