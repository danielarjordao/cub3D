#include "../../includes/cub3d.h"

int	ignore_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

char	*ft_trim_spaces(char *line)
{
	int		i;
	char	*new_line;

	line += ignore_spaces(line);
	i = ft_strlen(line) - 1;
	while (ft_isspace(line[i]))
		i--;
	new_line = ft_substr(line, 0, i + 1);
	return (new_line);
}

bool	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = ignore_spaces(line);
	if (!line[i])
		return (true);
	else
		return (false);
}
