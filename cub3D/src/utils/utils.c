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
	else if (err == MAP_FORMAT_ERR)
		ft_printf(2, "Map format error\n");
	else if (err == MAP_INVALID_CHAR)
		ft_printf(2, "Invalid character in map\n");
	else if (err == MISSING_INFO)
		ft_printf(2, "Missing information\n");
	else if (err == MAP_FORMAT_ERR)
		ft_printf(2, "Map format error\n");
	else if (err == MAP_INVALID_CHAR)
		ft_printf(2, "Invalid character in map\n");
	else
		ft_printf(2, "Unknown error %d\n", err);
	return (false);
}

void	*xpm_to_image(t_game *game, char *filename)
{
	void	*ptr_img;
	int		*ptr_width;
	int		*ptr_heigth;

	ptr_width = ft_calloc(1, sizeof(int));
	if (!ptr_width)
		destroy_free_exit_error(game, "ft_calloc failed");
	ptr_heigth = ft_calloc(1, sizeof(int));
	if (!ptr_width)
	{
		free(ptr_width);
		destroy_free_exit_error(game, "ft_calloc failed");
	}
	ptr_img = mlx_xpm_file_to_image(game->mlx->connection, filename, \
		ptr_width, ptr_heigth);
	printf("largura da imagem %d e deveria ser %d\n", *ptr_width, TEXTURE_WIDTH);
	printf("altuta da imagem %d e deveria ser %d\n", *ptr_heigth, TEXTURE_HEIGHT);
	if (*ptr_width != TEXTURE_WIDTH || *ptr_heigth != TEXTURE_HEIGHT)
	{
		free (ptr_width);
		free(ptr_heigth);
		mlx_destroy_image(game->mlx, ptr_img);
		destroy_free_exit_error(game, "The size of the img must be 256x256");
	}
	free (ptr_width);
	free(ptr_heigth);
	return (ptr_img);
}

int	close_game(t_game *game)
{
	printf("You left the game\n");
	call_destroy_functions(game);
	free_all(&(game->mem_alloc));
	exit(EXIT_SUCCESS);
}
