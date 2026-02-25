/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 12:12:20 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"

uint32_t	ft_get_pixel(mlx_image_t *texture, int col, int row)
{
	if ((uint32_t)col >= texture->width || (uint32_t)row >= texture->height || col < 0 || row < 0)
		return (0);
	uint32_t	pos = (row * texture->width + col) * 4;
	uint8_t r = texture->pixels[pos];
	uint8_t g = texture->pixels[pos + 1];
	uint8_t b = texture->pixels[pos + 2];
	uint8_t a = texture->pixels[pos + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}
