#include "../../includes/cub3d.h"

void	free_mem(void)
{
	ft_printf(1, "Freeing memory\n");
}

void	free_map(t_map *map)
{
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->we_texture)
		free(map->we_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->map)
		ft_free_matrix(map->map);
	free(map);
}
