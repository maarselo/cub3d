/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 15:02:55 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "game.h"

uint32_t	ft_get_pixel(int row, int col, mlx_image_t *texture)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	position;

	if ((uint32_t)col >= texture->width || (uint32_t)row >= texture->height
		|| col < 0 || row < 0)
		return (0);
	position = (row * texture->width + col) * 4;
	r = texture->pixels[position];
	g = texture->pixels[position + 1];
	b = texture->pixels[position + 2];
	a = texture->pixels[position + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	ft_end_game(t_data *data)
{
	return (data->game_over == KILL_ALL_ENEMIES || data->game_over == DIE);
}
