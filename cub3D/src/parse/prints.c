/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-souz <mde-souz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:56:35 by dramos-j          #+#    #+#             */
/*   Updated: 2025/04/11 11:44:57 by mde-souz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_map(t_map *map)
{
	if (!map)
		return ;
	printf("PRINTING MAP\n\n");
	if (map->no_texture && map->so_texture && map->we_texture
		&& map->ea_texture)
	{
		printf("North texture: %s\n", map->no_texture);
		printf("South texture: %s\n", map->so_texture);
		printf("West texture: %s\n", map->we_texture);
		printf("East texture: %s\n\n", map->ea_texture);
	}
	printf("Floor color[0]: %d\n", map->floor_color[0]);
	printf("Floor color[1]: %d\n", map->floor_color[1]);
	printf("Floor color[2]: %d\n\n", map->floor_color[2]);
	printf("Floor color hex:%X\n\n", map->floor_color_hex);
	printf("Ceiling color[0]: %d\n", map->ceiling_color[0]);
	printf("Ceiling color[1]: %d\n", map->ceiling_color[1]);
	printf("Ceiling color[2]: %d\n\n", map->ceiling_color[2]);
	printf("Ceiling color hex: %X\n\n", map->ceiling_color_hex);
	print_map2(map);
}

void	print_map2(t_map *map)
{
	int	i;
	int	j;

	if (map->map)
	{
		i = 0;
		printf("MAP\n");
		while (map->map[i])
		{
			j = 0;
			if (i < 9)
				printf("Line %d:  ", i + 1);
			else
				printf("Line %d: ", i + 1);
			while (map->map[i][j])
			{
				printf("%c", map->map[i][j]);
				j++;
			}
			i++;
		}
	}
	printf("\n");
	printf("Map width: %d\n", map->map_width);
	printf("Map height: %d\n", map->map_height);
	printf("Player x: %f\n", map->player_x);
	printf("Player y: %f\n", map->player_y);
	printf("Player direction: %c\n", map->player_dir);
	printf("\n");
}
