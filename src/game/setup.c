/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 12:53:08 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "parser.h"//t_map

void	ft_put_weapon_images(t_data *data)
{
	int	row;

	row = WINDOW_HEIGHT - data->textures->weapon->idle->height;
	mlx_image_to_window(data->mlx->window, data->textures->weapon->idle,
		WINDOW_WIDTH / 2, row);
	row = WINDOW_HEIGHT - data->textures->weapon->shoot->height;
	mlx_image_to_window(data->mlx->window, data->textures->weapon->shoot,
		WINDOW_WIDTH / 2, row);
	data->textures->weapon->shoot->enabled = false;
	row = WINDOW_HEIGHT - data->textures->weapon->smoke->height;
	mlx_image_to_window(data->mlx->window, data->textures->weapon->smoke,
		WINDOW_WIDTH / 2, row);
	data->textures->weapon->smoke->enabled = false;
}
