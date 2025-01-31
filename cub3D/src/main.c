/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dramos-j <dramos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 14:44:44 by dramos-j          #+#    #+#             */
/*   Updated: 2025/01/31 18:13:48 by dramos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

int	main(void)
{
	init_data();
	parsing();
	raycasting();
	render();
	start_game();
	handle_events();
	utils();
	free_mem();
	return (0);
}
