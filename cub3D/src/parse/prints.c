#include "../../includes/cub3d.h"

void	print_map(t_map *map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	printf("PRINTING MAP\n\n");
	if (map->no_texture)
		printf("North texture: %s\n", map->no_texture);
	if (map->so_texture)
		printf("South texture: %s\n", map->so_texture);
	if (map->we_texture)
		printf("West texture: %s\n", map->we_texture);
	if (map->ea_texture)
		printf("East texture: %s\n", map->ea_texture);
	printf("\n");
	i = 0;
	while (i < 3)
	{
		printf("Floor color[%d]: %d\n", i, map->floor_color[i]);
		i++;
	}
	printf("Floor color hex:%X\n", map->floor_color_hex);
	printf("\n");
	i = 0;
	while (i < 3)
	{
		printf("Ceiling color[%d]: %d\n", i, map->ceiling_color[i]);
		i++;
	}
	printf("Ceiling color hex: %X\n", map->ceiling_color_hex);
	printf("\n");
	if (map->map)
	{
		i = 0;
		printf("MAP\n");
		while (map->map[i])
		{
			j = 0;
			printf("Line %d: ", i);
			while (map->map[i][j])
			{
				printf("%c", map->map[i][j]);
				j++;
			}
			i++;
		}
	}
	printf("\n");
}
