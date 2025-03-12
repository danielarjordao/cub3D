/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:27:12 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/12 15:56:05 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ignore_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (i);
}

char	*ft_trim_spaces(char *line)
{
	int		i;
	char	*new_line;

	line += ignore_spaces(line);
	i = ft_strlen(line) - 1;
	while (ft_isspace(line[i]))
		i--;
	new_line = ft_substr(line, 0, i + 1);
	return (new_line);
}

bool	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = ignore_spaces(line);
	if (!line[i])
		return (true);
	else
		return (false);
}

bool	check_empty_lines_in_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		if (is_empty_line(map->map[i]))
		{
			j = i;
			while (map->map[i] && is_empty_line(map->map[i]))
				i++;
			if (!map->map[i])
			{
				clean_extra_empty_lines(map, j);
				return (false);
			}
			else
				return (true);
		}
		i++;
	}
	return (false);
}

void	clean_extra_empty_lines(t_map *map, int i)
{
	int	j;

	j = i;
	while (map->map[j])
	{
		free(map->map[j]);
		map->map[j] = NULL;
		j++;
	}
	map->map_height = i;
}
