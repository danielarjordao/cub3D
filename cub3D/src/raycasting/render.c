#include "../../includes/cub3d.h"

char	*get_pixel_from_texture(double x_wall, double y_wall)
{
	int	pixel_x;
	int	pixel_y;
	
	pixel_x = (int)round(255 * x_wall);
	pixel_y = (int)round(255 * y_wall);

	double wallX; // Onde exatamente a parede foi atingida (0.0 a 1.0)
	if (side == 0) // Parede vertical
	wallX = posY + perpWallDist * rayDirY;
	else // Parede horizontal
	wallX = posX + perpWallDist * rayDirX;

	// Pega apenas a parte fracionária desta coordenada.
	// Isto dá a posição X relativa dentro da célula da parede.
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)TEXTURE_WIDTH);

	// Verifica se precisas de inverter a coordenada X da textura
	// (depende se estás a olhar para uma parede Este vs Oeste, ou Norte vs Sul)
	if(side == 0 && rayDirX > 0) texX = TEXTURE_WIDTH - texX - 1;
	if(side == 1 && rayDirY < 0) texX = TEXTURE_WIDTH - texX - 1;
}


void	render(t_game *game, int x_screen, int wall_height)
{
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
	//Drawing ceiling
	while (y_screen < wall_start)
	{
		*(unsigned int *)pixel_ptr = game->map->ceiling_color_hex;
		pixel_ptr += game->mlx->size_line;
		y_screen++;
	}
	//Drawing wall
	while (y_screen <= wall_end)
	{
		//TODO - PRINTAR PAREDE
		*(unsigned int *)pixel_ptr = 0xff0000;
		pixel_ptr += game->mlx->size_line;
		y_screen++;
	}
	//Drawing floor
	while (y_screen < SCREEN_HEIGHT)
	{
		*(unsigned int *)pixel_ptr = game->map->floor_color_hex;
		pixel_ptr += game->mlx->size_line;
		y_screen++;
	}
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
