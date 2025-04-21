/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 19:46:53 by mde-souz          #+#    #+#             */
/*   Updated: 2025/04/21 19:46:54 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else
		return (msg_error2(err));
	return (false);
}

bool	msg_error2(t_error err)
{
	if (err == MAP_FORMAT_ERR)
		ft_printf(2, "Map format error\n");
	else if (err == MAP_INVALID_CHAR)
		ft_printf(2, "Invalid character in map\n");
	else if (err == MAP_PLAYER_DUP)
		ft_printf(2, "Player duplicated\n");
	else if (err == MAP_NO_PLAYER)
		ft_printf(2, "No player found\n");
	else if (err == MAP_BORDER_ERR)
		ft_printf(2, "Map border error\n");
	else
		ft_printf(2, "Unknown error %d\n", err);
	return (false);
}

void	xpm_to_image(t_game *game, t_texture *texture, char *filename)
{
	void	*ptr_img;
	int		width;
	int		heigth;

	ptr_img = mlx_xpm_file_to_image(game->mlx->connection, filename, \
		&width, &heigth);
	if (!ptr_img)
		destroy_free_exit_error(game, "mlx_xpm_file_to_image failed");
	if (width != TEX_WIDTH || heigth != TEX_HEIGHT)
	{
		mlx_destroy_image(game->mlx->connection, ptr_img);
		destroy_free_exit_error(game, "The size of the img must be 256x256");
	}
	texture->img = ptr_img;
	texture->pixel_address = \
		mlx_get_data_addr(texture->img, \
		&(texture->bpp), &(texture->size_line), \
		&(texture->endian));
}

int	close_game(t_game *game)
{
	printf("You left the game\n");
	call_destroy_functions(game);
	free_map(game->map);
	ft_free_t_mem_alloc(&(game->mem_alloc));
	exit(EXIT_SUCCESS);
}
