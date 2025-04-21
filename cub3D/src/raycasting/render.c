/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:24 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:24 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

unsigned int	get_pixel_from_texture(t_game *game, \
	int y_screen, int wall_start)
{
	int				tex_y;
	int				tex_x;
	unsigned int	*pixel_from_texture;
	double			wall_x;
	t_orient	tex_orientation;

	//De acordo com o grid atingido calcula o ponto x to choque
	if (game->ray.hit_grid == VERTICAL)
		wall_x = game->map->player_y + game->ray.perp_wall_dist * game->ray.dir_y;
	else
		wall_x = game->map->player_x + game->ray.perp_wall_dist * game->ray.dir_x;
	// Pega apenas a parte fracionária desta coordenada.
	// Isto dá a posição X relativa dentro da célula da parede.
	wall_x -= floor(wall_x);
	tex_x = get_x_pixel_position(game, wall_x);
	tex_y = get_y_pixel_position(game, y_screen, wall_start);
	//verifica qual sera a textura utilizada
	tex_orientation = get_texture_orientation(game);
	//pega o pixel da textura
	pixel_from_texture = \
		(unsigned int *)(game->textures[tex_orientation].pixel_address \
		+ (tex_x * game->textures[tex_orientation].bpp / 8) + \
		(tex_y * game->textures[tex_orientation].size_line));
	return (*pixel_from_texture);
}

void	copy_gun_pixel_to_screen(t_game *game, int gun_x_offset, \
	int gun_y_offset, char	*pixel_screen_img)
{
	unsigned int	*pixel_from_texture;
	
	if (game->shooting == TRUE)
		pixel_from_texture = (unsigned int *)((game->gun_fire.pixel_address \
			+ (gun_x_offset) * TEX_WIDTH / (SCREEN_WIDTH / 3) * game->gun.bpp / 8) + \
			((gun_y_offset) * TEX_WIDTH / (SCREEN_WIDTH / 3) * game->gun.size_line));
	else
		pixel_from_texture = (unsigned int *)((game->gun.pixel_address \
			+ (gun_x_offset) * TEX_WIDTH / (SCREEN_WIDTH / 3) * game->gun.bpp / 8) + \
			((gun_y_offset) * TEX_WIDTH / (SCREEN_WIDTH / 3) * game->gun.size_line));
	// Calcula o endereço do pixel na imagem de renderização
	// Copia o pixel para a imagem de renderização
	if (*pixel_from_texture != 0xff000000)
		*(unsigned int *)pixel_screen_img = *pixel_from_texture;
}

void	render_gun(t_game *game, int x_screen)
{
	char	*pixel_screen_img;
	int		gun_start_x;
	int		gun_end_x;
	int		gun_start_y;
	int		y_screen;

	gun_start_x = SCREEN_WIDTH / 2 - (SCREEN_WIDTH / 3) / 2;
	gun_end_x = SCREEN_WIDTH / 2 + (SCREEN_WIDTH / 3) / 2 - 1;
	gun_start_y = SCREEN_HEIGHT - (SCREEN_WIDTH / 3);
	// Itera sobre cada pixel da imagem da arma
	if (x_screen >= gun_start_x && x_screen <= gun_end_x)
	{
		y_screen = gun_start_y;
		pixel_screen_img = (game->mlx->addr + (x_screen * game->mlx->bpp / 8) + \
			(y_screen * game->mlx->size_line));
		while (y_screen >= gun_start_y && y_screen < SCREEN_HEIGHT)
		{
			copy_gun_pixel_to_screen(game, x_screen - \
				gun_start_x, y_screen - gun_start_y, pixel_screen_img);
			y_screen++;
			pixel_screen_img += game->mlx->size_line;
		}
	}
}

void	draw_pixel_on_imagem(t_game *game, int x_screen, \
		int wall_start, int wall_end)
{
	int		y_screen;
	char	*pixel_ptr;

	y_screen = 0;
	pixel_ptr = game->mlx->addr + (x_screen * game->mlx->bpp / 8);
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
		*(unsigned int *)pixel_ptr = \
			(get_pixel_from_texture(game, y_screen, wall_start));
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

void	render(t_game *game, int x_screen, int wall_height)
{
	int	wall_start;
	int	wall_end;

	wall_start = (SCREEN_HEIGHT / 2 - wall_height / 2) - 1;
	if (wall_start < 0)
		wall_start = 0;
	wall_end = (SCREEN_HEIGHT / 2 + wall_height / 2) - 1;
	if (wall_end >= SCREEN_HEIGHT)
		wall_end = SCREEN_HEIGHT - 1;
	draw_pixel_on_imagem(game, x_screen, wall_start, wall_end);
	render_gun(game, x_screen);
}
