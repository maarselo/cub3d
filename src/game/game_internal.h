/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 14:23:54 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INTERNAL_H
# define GAME_INTERNAL_H

# include "MLX42.h"

uint32_t	ft_get_pixel(int row, int col, mlx_image_t *texture);
bool		ft_end_game(t_data *data);
#endif