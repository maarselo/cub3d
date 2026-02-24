/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 23:33:05 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_INTERNAL_H
# define GAME_INTERNAL_H

# include "cub3d.h"
# include "MLX42.h"

uint32_t	ft_get_pixel(mlx_image_t *texture, int col, int row);
void		ft_set_draw_pos(t_data *data);
void		ft_set_render_data(t_data *data, int curr_col);
void		ft_set_tex_params(t_data *data, mlx_image_t *wall_texture);
void		ft_set_delta_dist(t_data *data);
mlx_image_t	*ft_set_wall_texture(t_data *data, mlx_image_t *wall_texture);

#endif