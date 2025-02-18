#include "../../includes/cub3d.h"

bool	init_map(t_map **map)
{
	*map = (t_map *)malloc(sizeof(t_map));
	if (!*map)
		return (MALLOC_FAIL);
	(*map)->no_texture = NULL;
	(*map)->so_texture = NULL;
	(*map)->we_texture = NULL;
	(*map)->ea_texture = NULL;
	(*map)->map = NULL;
	(*map)->map_width = 0;
	(*map)->map_height = 0;
	(*map)->player_x = 0;
	(*map)->player_y = 0;
	(*map)->player_dir = 0;
	return (true);
}

void	init_mlx(void)
{
	ft_printf(1, "		Initializing mlx\n");
}

void	init_textures(void)
{
	ft_printf(1, "		Initializing textures\n");
}

void	init_raycasting(void)
{
	ft_printf(1, "		Initializing raycasting\n");
}
