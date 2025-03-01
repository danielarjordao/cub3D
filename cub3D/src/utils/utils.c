#include "../../includes/cub3d.h"

bool	msg_error(t_error err)
{
	ft_printf(2, "Error\n");
	if (err == MALLOC_FAIL)
		ft_printf(2, "Malloc failed\n");
	else if (err == W_NBR_ARGS)
		ft_printf(2, "Wrong number of arguments\n");
	else if (err == INVALID_EXT)
		ft_printf(2, "Wrong file extension\n");
	else if (err == OPEN_FAIL)
		ft_printf(2, "Could not open file\n");
	else if (err == TEX_OPEN_FAIL)
		ft_printf(2, "Wrong texture path\n");
	else if (err == TEX_INVALID_EXT)
		ft_printf(2, "Wrong texture extension\n");
	else if (err == TEX_PATH_DUP)
		ft_printf(2, "Texture path duplicated\n");
	else if (err == COL_FORMAT_ERR)
		ft_printf(2, "Wrong color format\n");
	else if (err == COL_DUPLICATE)
		ft_printf(2, "Color duplicated\n");
	else if (err == MISSING_INFO)
		ft_printf(2, "Missing information\n");
	else if (err == MAP_FORMAT_ERR)
		ft_printf(2, "Map format error\n");
	else if (err == MAP_INVALID_CHAR)
		ft_printf(2, "Invalid character in map\n");
	else
		ft_printf(2, "Unknown error\n");
	return (false);
}
