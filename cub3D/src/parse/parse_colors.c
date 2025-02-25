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
		return (add_color(temp, (*map)->floor_color));
	else if (c == 'C')
		return (add_color(temp, (*map)->ceiling_color));
	else
		return (false);
}
// checar esse teste: C  						 	0, 0,0 8

bool	add_color(char **temp, int *color)
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
		if (is_empty_line(temp[i]))
		{
			ft_free_matrix(temp);
			return (msg_error(COL_FORMAT_ERR));
		}
		color[i] = ft_atoi(temp[i]);
		if (color[i] < 0 || color[i] > 255)
		{
			printf("color[%d]: %d\n", i, color[i]);
			ft_free_matrix(temp);
			return (msg_error(COL_FORMAT_ERR));
		}
		i++;
	}
	ft_free_matrix(temp);
	return (true);
}
