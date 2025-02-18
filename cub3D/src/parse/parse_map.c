#include "../../includes/cub3d.h"

bool	is_map_valid(char *line, t_map **map)
{
	int	i;

	(void)map;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && !is_space(line[i]))
		{
			return (false);
		}
		i++;
	}
	printf("Map: %s\n", line);
	return (true);
}
