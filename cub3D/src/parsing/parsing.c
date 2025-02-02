#include "../../includes/cub3d.h"

void	parsing(char *file)
{
	(void)file;
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
}
