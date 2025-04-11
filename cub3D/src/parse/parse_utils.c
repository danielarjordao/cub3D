/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:27:12 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/24 17:28:25 by dramos-j         ###   ########.fr       */
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
	if (!new_line)
		return ((char *)msg_error(MALLOC_FAIL));
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

bool	check_null_line(t_map *map, int i, int j)
{
	while (j < i)
	{
		if (!map->map[j] || !ft_strcmp(map->map[j], "\n")
			|| map->map[j][0] == '\r')
			return (true);
		j++;
	}
	return (false);
}
