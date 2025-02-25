#include "../../includes/cub3d.h"

void	print_map(t_map *map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	if (map->no_texture)
		printf("North texture: %s\n", map->no_texture);
	if (map->so_texture)
		printf("South texture: %s\n", map->so_texture);
	if (map->we_texture)
		printf("West texture: %s\n", map->we_texture);
	if (map->ea_texture)
	printf("East texture: %s\n", map->ea_texture);
	i = 0;
	while (map->floor_color[i])
	{
		printf("i: %d\n", i);
		printf("Floor color: %d\n", map->floor_color[i]);
		i++;
	}
	i = 0;
	while (map->ceiling_color[i])
	{
		printf("Ceiling color: %d\n", map->ceiling_color[i]);
		i++;
	}
	if (map->map)
	{
		i = 0;
		printf("Map:\n");
		while (map->map[i])
		{
			j = 0;
			while (map->map[i][j])
			{
				printf("%c", map->map[i][j]);
				j++;
			}
			printf("\n");
			i++;
		}
	}
}
