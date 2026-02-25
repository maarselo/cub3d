/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 17:45:15 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "parser.h"
#include "../game_internal.h"

void	ft_set_enemy_data(t_data *data, t_enemy *curr)
{
	data->enemy_render->sprite_x = curr->pos_x - data->player->pos_x;
	data->enemy_render->sprite_y = curr->pos_y - data->player->pos_y;
	data->enemy_render->inverse_det = 1 / (data->player->plane_x
			* data->player->dir_y - data->player->dir_x
			* data->player->plane_y);
	data->enemy_render->trans_x = data->enemy_render->inverse_det
		* (data->player->dir_y * data->enemy_render->sprite_x
			- data->player->dir_x * data->enemy_render->sprite_y);
	data->enemy_render->trans_y = data->enemy_render->inverse_det
		* (-data->player->plane_y * data->enemy_render->sprite_x
			+ data->player->plane_x * data->enemy_render->sprite_y);
	data->enemy_render->screen_x = (WINDOW_WIDTH / 2)
		* (1 + data->enemy_render->trans_x
			/ data->enemy_render->trans_y);
	data->enemy_render->size = fabs((WINDOW_HEIGHT
				/ data->enemy_render->trans_y) / 1.5);
	data->enemy_render->draw_end_y = (data->enemy_render->size / 2)
		+ (WINDOW_HEIGHT / 2) + (int)(175.0 / data->enemy_render->trans_y);
	data->enemy_render->draw_start_y = data->enemy_render->draw_end_y
		- data->enemy_render->size;
}

void	ft_get_enemy_draw_limits(t_data *data)
{
	if (data->enemy_render->draw_start_y < 0)
		data->enemy_render->draw_start_y = 0;
	if (data->enemy_render->draw_end_y >= WINDOW_HEIGHT)
		data->enemy_render->draw_end_y = WINDOW_HEIGHT - 1;
	data->enemy_render->draw_start_x = -(data->enemy_render->size / 2)
		+ data->enemy_render->screen_x;
	data->enemy_render->draw_end_x = (data->enemy_render->size / 2)
		+ data->enemy_render->screen_x;
	if (data->enemy_render->draw_start_x < 0)
		data->enemy_render->draw_start_x = 0;
	if (data->enemy_render->draw_end_x >= WINDOW_WIDTH)
		data->enemy_render->draw_end_x = WINDOW_WIDTH - 1;
}

void	ft_put_enemy_line(t_data *data, mlx_image_t *frame, int x, int y)
{
	uint32_t	color;

	data->enemy_render->d = (y - (int)(175.0
				/ data->enemy_render->trans_y)) * 256
		- WINDOW_HEIGHT * 128 + data->enemy_render->size * 128;
	data->enemy_render->tex_y = ((data->enemy_render->d
				* frame->height) / data->enemy_render->size) / 256;
	color = ft_get_pixel(data->enemy_render->tex_y,
			data->enemy_render->tex_x, frame);
	if ((color & 0x000000FF) != 0)
		mlx_put_pixel(data->mlx->framebuffer, x, y, color);
}
