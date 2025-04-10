#include "../../includes/cub3d.h"

unsigned int	get_pixel_from_texture(t_game *game, int y_screen, int wall_start)
{
	int 	tex_y;
	int	tex_x;
	unsigned int	*pixel_from_texture;
	double	wall_x; // Onde exatamente a parede foi atingida (0.0 a 1.0)

	if (game->ray.hit_grid == VERTICAL) // Parede vertical
		wall_x = game->map->player_y + game->ray.perpWallDist * game->ray.dir_y;
	else // Parede horizontal
		wall_x = game->map->player_x + game->ray.perpWallDist * game->ray.dir_x;

	// Pega apenas a parte fracionária desta coordenada.
	// Isto dá a posição X relativa dentro da célula da parede.
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)TEXTURE_WIDTH);

	// Verifica se precisas de inverter a coordenada X da textura
	// (depende se estás a olhar para uma parede Este vs Oeste, ou Norte vs Sul)
	
	
	if(game->ray.hit_grid == VERTICAL && game->ray.dir_x < 0)
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	else if(game->ray.hit_grid == HORIZONTAL && game->ray.dir_y > 0)
		tex_x = TEXTURE_WIDTH - tex_x - 1;
	
	if (game->ray.wall_height <= SCREEN_HEIGHT)
		tex_y = (int)((y_screen - wall_start) * ((double)TEXTURE_HEIGHT / game->ray.wall_height));
	else
		tex_y = (int)((y_screen - wall_start + (game->ray.wall_height - SCREEN_HEIGHT) / 2) * ((double)TEXTURE_HEIGHT / game->ray.wall_height));
	if (tex_y >= TEXTURE_HEIGHT) // Evita overflow
		tex_y = TEXTURE_HEIGHT - 1;
	
	//verifica qual sera a textura utilizada
	t_orientation orientation;

	if(game->ray.hit_grid == VERTICAL && game->ray.dir_x > 0)
		orientation = WE;
	else if(game->ray.hit_grid == VERTICAL && game->ray.dir_x < 0)
		orientation = EA;
	else if(game->ray.hit_grid == HORIZONTAL && game->ray.dir_y > 0)
		orientation = NO;
	else
		orientation = SO;
	
	//pega o pixel da textura
	pixel_from_texture = (unsigned int *) (game->textures[orientation].pixel_address \
		+ (tex_x * game->textures[orientation].bpp / 8) + \
		(tex_y * game->textures[orientation].size_line));
	
	return (*pixel_from_texture);
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
	while (y_screen < wall_end)
	{
		*(unsigned int *)pixel_ptr = (get_pixel_from_texture(game, y_screen, wall_start));
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
