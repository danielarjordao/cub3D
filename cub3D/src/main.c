/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:44:44 by dramos-j          #+#    #+#             */
/*   Updated: 2025/03/24 13:01:14 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (msg_error(W_NBR_ARGS));
	if (!parse(argv[1], &game.map))
		return (1);
	//start_game(&game);
	free_map(game.map);
	return (0);
}
