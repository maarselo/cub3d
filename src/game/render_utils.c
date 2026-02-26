/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/26 17:23:33 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include <math.h>

void	ft_set_draw_pos(t_data *data)
{
	data->render->wall.draw_start = (WINDOW_HEIGHT
			- data->render->wall.wall_height) / 2;
	data->render->wall.draw_end = data->render->wall.draw_start
		+ data->render->wall.wall_height;
	if (data->render->wall.draw_start < 0)
		data->render->wall.draw_start = 0;
	if (data->render->wall.draw_end >= WINDOW_HEIGHT)
		data->render->wall.draw_end = WINDOW_HEIGHT - 1;
}

void	ft_set_render_data(t_data *data, int curr_col)
{
	data->render->camera_x = 2 * curr_col / (double)WINDOW_WIDTH - 1;
	data->render->ray_dir_x = data->player->dir_x
		+ (data->player->plane_x * data->render->camera_x);
	data->render->ray_dir_y = data->player->dir_y
		+ (data->player->plane_y * data->render->camera_x);
	data->render->map_x = (int)data->player->pos_x;
	data->render->map_y = (int)data->player->pos_y;
}

void	ft_set_tex_params(t_data *data, mlx_image_t *wall_texture)
{
	data->render->wall.tex_x = (int)((double)wall_texture->width
			* data->render->wall.wall_x);
	data->render->wall.step = (double)wall_texture->height
		/ data->render->wall.wall_height;
	data->render->wall.tex_pos = (data->render->wall.draw_start
			- WINDOW_HEIGHT / 2 + data->render->wall.wall_height / 2)
		* data->render->wall.step;
}

void	ft_set_delta_dist(t_data *data)
{
	if (data->render->ray_dir_x != 0)
		data->render->delta_dist_x = fabs(1 / data->render->ray_dir_x);
	else
		data->render->delta_dist_x = 1e30;
	if (data->render->ray_dir_y != 0)
		data->render->delta_dist_y = fabs(1 / data->render->ray_dir_y);
	else
		data->render->delta_dist_y = 1e30;
}

mlx_image_t	*ft_set_wall_texture(t_data *data,
			mlx_image_t *wall_texture)
{
	if (!wall_texture)
	{
		if (data->render->wall.side == 0)
		{
			if (data->render->step_x == -1)
				wall_texture = data->textures->east;
			else
				wall_texture = data->textures->west;
		}
		else
		{
			if (data->render->step_y == -1)
				wall_texture = data->textures->south;
			else
				wall_texture = data->textures->north;
		}
	}
	return (wall_texture);
}
