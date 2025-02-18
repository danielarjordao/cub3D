/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:44:44 by dramos-j          #+#    #+#             */
/*   Updated: 2025/02/18 18:49:06 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (msg_error(W_NBR_ARGS));
	if (!parse(argv[1], &map))
		return (1);
//	start_game();
//	free_mem();
	free_map(map);
	return (0);
}
