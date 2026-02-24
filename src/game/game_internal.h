/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 19:55:33 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INTERNAL
# define GAME_INTERNAL

# include "cub3d.h"
#include "MLX42.h"

uint32_t	ft_get_pixel(mlx_image_t *texture, int col, int row);

#endif