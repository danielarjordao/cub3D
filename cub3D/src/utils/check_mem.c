#include "../../includes/cub3d.h"

void	check_mem(t_game *game, t_list **ptr_or_matrix_list, \
	void *ptr, char *error_msg)
{
	if (!ptr)
		destroy_free_exit_error(game, error_msg);
	else
		ft_save_pointer(&(game->mem_alloc), ptr_or_matrix_list, ptr);
}

void	if_not_null_destroy(t_game *game, void *img_ptr)
{
	if (img_ptr != NULL)
		mlx_destroy_image(game->mlx->connection, img_ptr);
}

void	call_destroy_functions(t_game *game)
{
	if_not_null_destroy(game, game->textures[NO].img);
	if_not_null_destroy(game, game->textures[SO].img);
	if_not_null_destroy(game, game->textures[WE].img);
	if_not_null_destroy(game, game->textures[EA].img);
	if_not_null_destroy(game, game->gun.img);
	if_not_null_destroy(game, game->gun_fire.img);
	if (game->mlx)
	{
		if (game->mlx->img_to_render != NULL)
			mlx_destroy_image(game->mlx->connection, game->mlx->img_to_render);
		if (game->mlx->win != NULL)
			mlx_destroy_window(game->mlx->connection, game->mlx->win);
		if (game->mlx->connection != NULL)
			mlx_destroy_display(game->mlx->connection);
	}
}

void	free_exit_error(t_mem_alloc *mem_allocation, \
	char *error_msg)
{
	if (errno != 0 && errno != 11)
		ft_printf(2, "Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	ft_free_t_mem_alloc(mem_allocation);
	exit(EXIT_FAILURE);
}

void	destroy_free_exit_error(t_game *game, char *error_msg)
{
	call_destroy_functions(game);
	free_map(game->map);
	get_next_line(-1);
	free_exit_error(&(game->mem_alloc), error_msg);
}
