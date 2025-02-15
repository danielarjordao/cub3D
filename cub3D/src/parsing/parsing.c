#include "../../includes/cub3d.h"

bool	check_file_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	file += len - 4;
	if (!file || len <= 4 || ft_strncmp(file, ".cub", 4) != 0)
		return (false);
	return (true);
}

bool	parsing(char *file)
{
	if (check_file_extension(file) == false)
		return (msg_error(W_EXTENSION));
	ft_printf(1, "Initiating parsing\n");
	ft_printf(1, "		Checking file extension\n");
	ft_printf(1, "		Opening file\n");
	ft_printf(1, "		Checking texture paths\n");
	ft_printf(1, "		Checking colors\n");
	ft_printf(1, "		Checking map parameters\n");
	ft_printf(1, "		Checking map structure\n");
	init_map();
	ft_printf(1, "		Saving map parameters\n");
	ft_printf(1, "Parsing complete\n\n");
	return (true);
}
