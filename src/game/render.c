/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 21:22:35 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "parser.h"
#include "game.h"
#include "game_internal.h"

void	ft_render(void *param)
{
	int			current_col;
	int			i;
	double		step;
	double		tex_pos;
	mlx_image_t	*wall_texture;
	t_data		*data;

	data = (t_data *)param;
	current_col = -1;
	while (++current_col < WINDOW_WIDTH)
	{
		wall_texture = NULL;
		data->render->camera_x = 2 * current_col / (double)WINDOW_WIDTH - 1;
		data->render->ray_dir_x = data->player->dir_x
			+ (data->player->plane_x * data->render->camera_x);
		data->render->ray_dir_y = data->player->dir_y
			+ (data->player->plane_y * data->render->camera_x);
		data->render->map_x = (int)data->player->pos_x;
		data->render->map_y = (int)data->player->pos_y;
		if (data->render->ray_dir_x != 0)
			data->render->delta_dist_x = fabs(1 / data->render->ray_dir_x);
		else
			data->render->delta_dist_x = 1e30;
		if (data->render->ray_dir_y != 0)
			data->render->delta_dist_y = fabs(1 / data->render->ray_dir_y);
		else
			data->render->delta_dist_y = 1e30;
		if (data->render->ray_dir_x < 0)
		{
			data->render->step_x = -1;
			data->render->side_dist_x = (data->player->pos_x
					- data->render->map_x) * data->render->delta_dist_x;
		}
		else
		{
			data->render->step_x = 1;
			data->render->side_dist_x = (data->render->map_x + 1.0
					- data->player->pos_x) * data->render->delta_dist_x;
		}
		if (data->render->ray_dir_y < 0)
		{
			data->render->step_y = -1;
			data->render->side_dist_y = (data->player->pos_y
					- data->render->map_y) * data->render->delta_dist_y;
		}
		else
		{
			data->render->step_y = 1;
			data->render->side_dist_y = (data->render->map_y + 1.0
					- data->player->pos_y) * data->render->delta_dist_y;
		}
		data->render->wall->hit = false;
		while (!data->render->wall->hit)
		{
			if (data->render->side_dist_x < data->render->side_dist_y)
			{
				data->render->side_dist_x += data->render->delta_dist_x;
				data->render->map_x += data->render->step_x;
				data->render->wall->side = 0;
			}
			else
			{
				data->render->side_dist_y += data->render->delta_dist_y;
				data->render->map_y += data->render->step_y;
				data->render->wall->side = 1;
			}
			if (data->map->map[data->render->map_y][data->render->map_x] == '1')
				data->render->wall->hit = true;
			else if (data->map->map[data->render->map_y][data->render->map_x]
				== '_'
				|| data->map->map[data->render->map_y][data->render->map_x]
				== '|')
			{
				data->render->wall->hit = true;
				wall_texture = data->textures->door;
			}
		}
		if (data->render->wall->side == 0)
		{
			data->render->wall->perpend_dist = data->render->side_dist_x
				- data->render->delta_dist_x;
			data->render->wall->wall_x = data->player->pos_y
				+ data->render->ray_dir_y * data->render->wall->perpend_dist;
		}
		else
		{
			data->render->wall->perpend_dist = data->render->side_dist_y
				- data->render->delta_dist_y;
			data->render->wall->wall_x = data->player->pos_x
				+ data->render->ray_dir_x * data->render->wall->perpend_dist;
		}
		data->render->wall->wall_x -= floor(data->render->wall->wall_x);
		data->render->wall->wall_height = (int)(WINDOW_HEIGHT
				/ data->render->wall->perpend_dist);
		data->render->wall->draw_start = (WINDOW_HEIGHT
				- data->render->wall->wall_height) / 2;
		data->render->wall->draw_end = data->render->wall->draw_start
			+ data->render->wall->wall_height;
		if (data->render->wall->draw_start < 0)
			data->render->wall->draw_start = 0;
		if (data->render->wall->draw_end >= WINDOW_HEIGHT)
			data->render->wall->draw_end = WINDOW_HEIGHT - 1;
		if (!wall_texture)
		{
			if (data->render->wall->side == 0)
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
		data->render->wall->tex_x = (int)((double)wall_texture->width
				* data->render->wall->wall_x);
		step = (double)wall_texture->height / data->render->wall->wall_height;
		tex_pos = (data->render->wall->draw_start - WINDOW_HEIGHT / 2
				+ data->render->wall->wall_height / 2) * step;
		i = 0;
		while (i < data->render->wall->draw_start)
		{
			mlx_put_pixel(data->mlx->framebuffer, current_col,
				i, data->colors->floor);
			i++;
		}
		while (i < data->render->wall->draw_end)
		{
			mlx_put_pixel(data->mlx->framebuffer, current_col, i,
				ft_get_pixel(wall_texture, data->render->wall->tex_x,
					(int)tex_pos));
			tex_pos += step;
			i++;
		}
		while (i < WINDOW_HEIGHT)
		{
			mlx_put_pixel(data->mlx->framebuffer,
				current_col, i, data->colors->ceiling);
			i++;
		}
		data->mlx->z_buffer[current_col] = data->render->wall->perpend_dist;
	}
}
