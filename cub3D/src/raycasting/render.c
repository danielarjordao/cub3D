#include "../../includes/cub3d.h"

void	render(t_game *game, int x_screen, int wall_height)
{
	ft_printf(1, "Rendering\n");
	int	y_screen;
	char	*pixel_ptr;
	int wall_start;
	int wall_end;

	wall_start = (SCREEN_HEIGHT / 2 - wall_height / 2) - 1;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = (SCREEN_HEIGHT / 2 + wall_height / 2) - 1;
	if (wall_end >= SCREEN_HEIGHT)
		wall_end = SCREEN_HEIGHT - 1;
	
	y_screen = 0;
	pixel_ptr = (game->mlx->addr + (x_screen * game->mlx->bpp / 8) + (y_screen * game->mlx->size_line));
	ft_printf(1, "		Drawing ceiling\n");
	//Drawing ceiling
	while (y_screen < wall_start)
	{
		*(unsigned int *)pixel_ptr = game->map->ceiling_color_hex;
		pixel_ptr += game->mlx->size_line;
		y_screen++;
	}
	ft_printf(1, "		Drawing walls\n");
	//Drawing wall
	while (y_screen <= wall_end)
	{
		//TODO - PRINTAR PAREDE
		*(unsigned int *)pixel_ptr = 0xff0000;
		pixel_ptr += game->mlx->size_line;
		y_screen++;
	}
	//Drawing floor
	ft_printf(1, "		Drawing flor\n");
	while (y_screen < SCREEN_HEIGHT)
	{
		*(unsigned int *)pixel_ptr = game->map->floor_color_hex;
		pixel_ptr += game->mlx->size_line;
		y_screen++;
	}
	ft_printf(1, "Rendering complete\n\n");
}

/* #include "../../includes/cub3d.h"

void	render(t_game *game)
{
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
				*pixel_ptr = game->map->floor_color_hex;
			else
				*pixel_ptr = game->map->ceiling_color_hex;
			x_screen++;
		}
		y_screen++;
	}
	mlx_put_image_to_window(game->mlx->connection, game->mlx->win, game->mlx->img_to_render, 0 , 0);
	ft_printf(1, "		Drawing walls\n");
	ft_printf(1, "		Drawing textures\n");
	ft_printf(1, "		Updating window\n");
	ft_printf(1, "Rendering complete\n\n");
} */
