/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:19 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:20 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_orient	get_texture_orientation(t_game *game)
{
	if (game->ray.hit_grid == VERTICAL && game->ray.dir_x > 0)
		return (WE);
	else if (game->ray.hit_grid == VERTICAL && game->ray.dir_x < 0)
		return (EA);
	else if (game->ray.hit_grid == HORIZONTAL && game->ray.dir_y > 0)
		return (NO);
	else
		return (SO);
}

int	get_y_pixel_position(t_game *game, int y_screen, int wall_start)
{
	int		tex_y;
	int		relative_top_wall_y;
	int		offscreen_wall_height;
	double	texture_to_wall_ratio;

	relative_top_wall_y = y_screen - wall_start;
	if (game->ray.wall_height == 0)
		return (0);
	else
		texture_to_wall_ratio = ((double)TEX_HEIGHT / game->ray.wall_height);
	if (game->ray.wall_height <= SCREEN_HEIGHT)
		tex_y = (int)(relative_top_wall_y * texture_to_wall_ratio);
	else
	{
		offscreen_wall_height = (game->ray.wall_height - SCREEN_HEIGHT) / 2;
		tex_y = (int)((relative_top_wall_y + offscreen_wall_height) * \
			texture_to_wall_ratio);
	}
	if (tex_y >= TEX_HEIGHT)
		tex_y = TEX_HEIGHT - 1;
	else if (tex_y < 0)
		tex_y = 0;
	return (tex_y);
}

int	get_x_pixel_position(t_game *game, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)TEX_WIDTH);
	if (game->ray.hit_grid == VERTICAL && game->ray.dir_x < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	else if (game->ray.hit_grid == HORIZONTAL && game->ray.dir_y > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	else if (tex_x >= TEX_WIDTH)
		tex_x = TEX_WIDTH - 1;
	return (tex_x);
}
