# include "../../includes/cub3d.h"

void	render(t_game *game)
{
	game->mlx->img_to_render = mlx_new_image(game->mlx->connection, \
		SCREEN_WIDTH, SCREEN_HEIGHT);
	
	game->mlx->addr = mlx_get_data_addr(game->mlx->img_to_render, \
		&(game->mlx->bpp), &(game->mlx->size_line), &(game->mlx->endian));


	ft_printf(1, "Rendering\n");
	ft_printf(1, "		Drawing ceiling and floor\n");
	int	x_screen;
	int	y_screen;
	unsigned int	*pixel_ptr;
	
	y_screen = 0;
	while (y_screen < SCREEN_HEIGHT)
	{
		pixel_ptr = (unsigned int *) (game->mlx->addr + (y_screen * game->mlx->size_line));
		x_screen = 0;
		while (x_screen < SCREEN_WIDTH)
		{
			if (x_screen != 0)
				pixel_ptr++;
			if (y_screen < SCREEN_HEIGHT / 2)
				*pixel_ptr = 0x000000;
			else
				*pixel_ptr = 0xFFFFFF;
			x_screen++;
		}
		y_screen++;
	}
	mlx_put_image_to_window(game->mlx->connection, game->mlx->win, game->mlx->img_to_render, 0 , 0);
	ft_printf(1, "		Drawing walls\n");
	ft_printf(1, "		Drawing textures\n");
	ft_printf(1, "		Updating window\n");
	ft_printf(1, "Rendering complete\n\n");
}
