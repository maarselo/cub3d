/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/07 21:50:33 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "errorctx.h"
#include <math.h>

void	ft_render(void *param)
{
	int		current_x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	bool	hit;
	int		side; // 0 vertical x 1 horizontal y
	double	perpendicular_dist;
	int		wall_height;
	int		draw_start;
	int		draw_end;
	t_data	*data;

	data = (t_data *)param;
	current_x = -1;
	while (current_x++ < WINDOW_WIDTH)
	{
		camera_x = 2 * current_x / WINDOW_WIDTH - 1;
		ray_dir_x = data->player->dir_x + (data->player->plane_x * camera_x);
		ray_dir_y = data->player->dir_y + (data->player->plane_y * camera_x);
		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;
		if (ray_dir_x != 0)
			delta_dist_x = fabs(1 / ray_dir_x);
		else
			delta_dist_x = 1e30;
		if (ray_dir_y != 0)
			delta_dist_y = fabs(1 / ray_dir_y);
		else
			delta_dist_y = 1e30;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player->pos_y) * delta_dist_y;
		}
		hit = false;
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (data->map->map[map_y][map_x] == '1')
				hit = true;
		}
		if (side == 0)
			perpendicular_dist = side_dist_x - delta_dist_x;
		else
			perpendicular_dist = side_dist_y - delta_dist_y;
		wall_height = (int)(WINDOW_HEIGHT / perpendicular_dist);
		draw_start = (WINDOW_HEIGHT - wall_height) / 2;
		draw_end = draw_start + wall_height;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WINDOW_HEIGHT)
			draw_end = WINDOW_HEIGHT - 1;
		int	i = 0;
		while (i < draw_start)
		{
			mlx_put_pixel(data->mlx->img, current_x, i, data->colors->floor);
			i++;
		}
		while (i < draw_end)
		{
			mlx_put_pixel(data->mlx->img, current_x, i, 0xFF6F3FF5);
			i++;
		}
		while (i < WINDOW_HEIGHT)
		{
			mlx_put_pixel(data->mlx->img, current_x, i, data->colors->ceiling);
			i++;
		}
	}
}

void	ft_move(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_W)
		data->player->pos_y -= 0.1;
	if (key.key == MLX_KEY_S)
		data->player->pos_y += 0.1;
	if (key.key == MLX_KEY_A)
		data->player->pos_x -= 0.1;
	if (key.key == MLX_KEY_D)
		data->player->pos_x += 0.1;
}

void	ft_game_loop(t_data *data)
{
	mlx_loop_hook(data->mlx->window, ft_render, data);
	mlx_key_hook(data->mlx->window, ft_move, data);
	mlx_loop(data->mlx->window);
}
