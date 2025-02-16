#include "../../includes/cub3d.h"

bool	check_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	file += len - 4;
	if (!file || ft_strncmp(file, ".cub", 4) != 0)
		return (false);
	return (true);
}

bool	check_valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] < 9 || line[i] > 13) && line[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

bool	looking_for(char *line, char *str)
{
	int	i;

	i = 0;
	while ((line[i] > 9 && line[i] < 13) || line[i] == 32)
		i++;
	if (ft_strncmp(line + i, str, ft_strlen(str)) == 0)
		return (true);
	else
		return (false);
}

bool	check_line(char *line)
{
	if (empty_line(line) == true)
		return (true);
	else if (looking_for(line, "NO") == true)
		return (true);
	else if (looking_for(line, "SO") == true)
		return (true);
	else if (looking_for(line, "WE") == true)
		return (true);
	else if (looking_for(line, "EA") == true)
		return (true);
	else if (looking_for(line, "F") == true)
		return (true);
	else if (looking_for(line, "C") == true)
		return (true);
	else
		return (false);
	/*
	ft_printf(1, "		Checking texture paths\n");
	ft_printf(1, "		Checking colors\n");
	ft_printf(1, "		Checking map parameters\n");
	ft_printf(1, "		Checking map structure\n");
	*/
	return (true);
}

bool	check_file_content(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	init_map();
	ft_printf(1, "		Checking file content\n");
	line = get_next_line(fd);
	while (line)
	{
		if (check_line(line) == false)
		{
			free(line);
			close(fd);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	ft_printf(1, "		File content is valid\n");
	return (true);
}

bool	parsing(char *file)
{
	ft_printf(1, "Initiating parsing\n");
	if (check_file_extension(file) == false)
		return (msg_error(W_EXTENSION));
	else if (check_valid_file(file) == false)
		return (msg_error(W_OPEN));
	else if (check_file_content(file) == false)
	{
		ft_printf(1, "Parsing failed\n");
		ft_printf(1, "Freeing memory\n");
		return (false);
	}
	ft_printf(1, "Parsing complete\n\n");
	return (true);
}
