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

void	render_gun(t_game *game, int x_screen)
{
	unsigned int	*pixel_from_texture;
	char	*pixel_ptr;
	int	gun_start_x;
	int	gun_end_x;
	int	gun_start_y;
	int	y_screen;

	
	gun_start_x = SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 3) / 2;
	gun_end_x = SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 3) / 2 - 1;
	gun_start_y = SCREEN_HEIGHT - (SCREEN_WIDTH / 3);

	// Itera sobre cada pixel da imagem da arma
    
	if (x_screen >= gun_start_x && x_screen <= gun_end_x)
	{
		y_screen = gun_start_y;
		pixel_ptr = (game->mlx->addr + (x_screen * game->mlx->bpp / 8) + (y_screen * game->mlx->size_line));
		while (y_screen >= gun_start_y && y_screen < SCREEN_HEIGHT)
		{
			// Calcula o endereço do pixel na imagem da arma
			//src_pixel = game->gun.pixel_address + (y_screen * game->gun.size_line + x_screen * (game->gun.bpp / 8));
			pixel_from_texture = (unsigned int *)((game->gun.pixel_address \
					+ (x_screen - gun_start_x) * TEXTURE_WIDTH / (SCREEN_WIDTH / 3) * game->gun.bpp / 8) + \
					( (y_screen - gun_start_y) * TEXTURE_WIDTH / (SCREEN_WIDTH / 3) * game->gun.size_line));
			// Calcula o endereço do pixel na imagem de renderização
			// Copia o pixel para a imagem de renderização
			if (*pixel_from_texture != 0xff000000)
				*(unsigned int *)pixel_ptr = *pixel_from_texture;
			y_screen++;
			pixel_ptr += game->mlx->size_line;
		}
	}
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
	//REVIEW -> tentar pagar a parte  + (y_screen * game->mlx->size_line)
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
	render_gun(game, x_screen);
}
