#include "../../includes/cub3d.h"

void	raycasting(t_game *game)
{
	ft_printf(1, "Starting raycasting\n");
	ft_printf(1, "		Save player position and direction\n");
	ft_printf(1, "		Calculate ray direction\n");
	ft_printf(1, "		Use DDA algorithm\n");
	ft_printf(1, "		Calculate ray distance\n");
	ft_printf(1, "		Calculate wall height\n");
	ft_printf(1, "Raycasting complete\n\n");
	render(game);
}
