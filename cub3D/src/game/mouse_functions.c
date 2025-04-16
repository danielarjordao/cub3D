#include "../../includes/cub3d.h"

int	mouse_hook(int x, int y, t_game *game)
{
	(void)y;
	game->delta_x_mouse = x - SCREEN_WIDTH / 2;
	return (EXIT_SUCCESS);
}

int	handle_mouse_click(int button, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	(void) x;
	(void) y;
	if (button == Button1)
		game->shooting = TRUE;
	return (EXIT_SUCCESS);
}
