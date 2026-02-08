/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/08 21:55:56 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "errorctx.h"
#include <math.h>

void	ft_render(void *param)
{
	int		current_col; // current pixel column of the screen
	double	camera_x; // used to calculate in which side of the screen is current_col
	double	ray_dir_x; // direction of the ray casted on x axis
	double	ray_dir_y; // direction of the ray casted on y axis
	double	delta_dist_x; // how many pixels it takes for the ray to cross 1 whole x unit (vertical lines)
	double	delta_dist_y; // how many pixels it takes for the ray to cross 1 whole y unit (horizontal lines)
	double	side_dist_x; // distance to first vertical line
	double	side_dist_y; // distance to first horizontal line
	int		map_x; // player pos_x casted to int
	int		map_y; // player pos_y casted to int
	int		step_x; // used to know in which direction the player is going in the x axis
	int		step_y; // used to know in which direction the player is going in the y axis
	bool	hit; // used to knw if the ray hit a wall
	int		side; // to know if the ray passed a vertical or horizontal line first (0 vertical x 1 horizontal y)
	double	perpendicular_dist; // straight distance to the wall (avoid fisheye)
	int		wall_height; // how tall the wall looks on the screen
	int		draw_start; // point where you start to draw the wall
	int		draw_end; // point where you stop drawing the wall
	//mlx_texture_t	*tex;
	//double	wall_x; // in what x pixel of the wall the ray collides
	uint32_t	color;
	t_data	*data;

	data = (t_data *)param;
	current_col = -1;
	while (current_col++ < WINDOW_WIDTH)
	{
		camera_x = 2 * current_col / (double)WINDOW_WIDTH - 1;
		ray_dir_x = data->player->dir_x + (data->player->plane_x * camera_x);
		ray_dir_y = data->player->dir_y + (data->player->plane_y * camera_x);
		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;
		color = 0xFF6F3FF5;
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
		{
			perpendicular_dist = side_dist_x - delta_dist_x;
			//wall_x = data->player->pos_y + ray_dir_y * perpendicular_dist;
		}
		else
		{
			perpendicular_dist = side_dist_y - delta_dist_y;
			//wall_x = data->player->pos_x + ray_dir_x * perpendicular_dist;
			color = 0xFF6038D1;
		}
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
			mlx_put_pixel(data->mlx->img, current_col, i, data->colors->floor);
			i++;
		}
		while (i < draw_end)
		{
			mlx_put_pixel(data->mlx->img, current_col, i, color);
			i++;
		}
		/*if (side == 0 && data->player->dir_x == 1)
			tex = data->textures->east;
		else if (side == 0 && data->player->dir_x == -1)
			tex = data->textures->west;
		else if (side == 1 && data->player->dir_y == 1)
			tex = data->textures->south;
		else
			tex = data->textures->north;*/
		while (i < WINDOW_HEIGHT)
		{
			mlx_put_pixel(data->mlx->img, current_col, i, data->colors->ceiling);
			i++;
		}
	}
}

#include <stdlib.h>

void	ft_move(mlx_key_data_t key, void *param)
{
	t_data	*data;
	double	speed;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;
	double	buffer;

	data = (t_data *)param;
	speed = 0.2;
	rot_speed = 0.05;
	buffer = 0.2;
	if (key.key == MLX_KEY_ESCAPE)
		exit(1);
	if (key.key == MLX_KEY_W)
	{
		if (data->map->map[(int)(data->player->pos_y + data->player->dir_y * (speed + buffer))][(int)data->player->pos_x] == '0')
			data->player->pos_y += data->player->dir_y * speed;
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + data->player->dir_x * (speed + buffer))] == '0')
			data->player->pos_x += data->player->dir_x * speed;
	}
	if (key.key == MLX_KEY_S)
	{
		if (data->map->map[(int)(data->player->pos_y - data->player->dir_y * (speed + buffer))][(int)data->player->pos_x] == '0')
			data->player->pos_y -= data->player->dir_y * speed;
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x - data->player->dir_x * (speed + buffer))] == '0')
			data->player->pos_x -= data->player->dir_x * speed;
	}
	if (key.key == MLX_KEY_A)
	{
		if (data->map->map[(int)(data->player->pos_y - data->player->plane_y * (speed + buffer))][(int)data->player->pos_x] == '0')
			data->player->pos_y -= data->player->plane_y * speed;
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x - data->player->dir_x * (speed + buffer))] == '0')
			data->player->pos_x -= data->player->plane_x * speed;
	}
	if (key.key == MLX_KEY_D)
	{
		if (data->map->map[(int)(data->player->pos_y + data->player->plane_y * (speed + buffer))][(int)data->player->pos_x] == '0')
			data->player->pos_y += data->player->plane_y * speed;
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + data->player->plane_x * (speed + buffer))] == '0')
			data->player->pos_x += data->player->plane_x * speed;
	}
	if (key.key == MLX_KEY_LEFT)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = old_dir_x * cos(speed) - data->player->dir_y * sin(speed);
		data->player->dir_y = old_dir_x * sin(speed) + data->player->dir_y * cos(speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = old_plane_x * cos(speed) - data->player->plane_y * sin(speed);
		data->player->plane_y = old_plane_x * sin(speed) + data->player->plane_y * cos(speed);
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = old_dir_x * cos(-speed) - data->player->dir_y * sin(-speed);
		data->player->dir_y = old_dir_x * sin(-speed) + data->player->dir_y * cos(-speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = old_plane_x * cos(-speed) - data->player->plane_y * sin(-speed);
		data->player->plane_y = old_plane_x * sin(-speed) + data->player->plane_y * cos(-speed);
	}
}

void	ft_game_loop(t_data *data)
{
	mlx_loop_hook(data->mlx->window, ft_render, data);
	mlx_key_hook(data->mlx->window, ft_move, data);
	mlx_loop(data->mlx->window);
}
