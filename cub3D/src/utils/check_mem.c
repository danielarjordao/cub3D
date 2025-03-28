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
		mlx_destroy_image(game->mlx, img_ptr);
}

void	call_destroy_functions(t_game *game)
{
	//TODO -> Destruir todas os ponteiros de imagens já criados
	//if_not_null_destroy(game, game->image);

	if (game->mlx->win != NULL)
		mlx_destroy_image(game->mlx->connection, game->mlx->img_to_render);
	if (game->mlx->win != NULL)
		mlx_destroy_window(game->mlx->connection, game->mlx->win);
	if (game->mlx->connection != NULL)
		mlx_destroy_display(game->mlx->connection);
}

void	free_all(t_mem_alloc *mem_allocation)
{
	if (mem_allocation->ptr_mem_list != NULL)
		ft_lstclear(&(mem_allocation->ptr_mem_list), free);
	if (mem_allocation->matrix_mem_list != NULL)
		ft_lstclear(&(mem_allocation->matrix_mem_list), ft_free_matrix);
}

void	free_exit_error(t_mem_alloc *mem_allocation, \
	char *error_msg)
{
	if (errno != 0 && errno != 11)
		ft_printf(2, "Error\n%s: %s\n", error_msg, strerror(errno));
	else
		ft_printf(2, "Error\n%s\n", error_msg);
	if (mem_allocation->ptr_mem_list != NULL)
		ft_lstclear(&(mem_allocation->ptr_mem_list), free);
	if (mem_allocation->matrix_mem_list != NULL)
		ft_lstclear(&(mem_allocation->matrix_mem_list), ft_free_matrix);
	exit(EXIT_FAILURE);
}

void	destroy_free_exit_error(t_game *game, char *error_msg)
{
	call_destroy_functions(game);
	get_next_line(-1);
	free_exit_error(&(game->mem_alloc), error_msg);
}

