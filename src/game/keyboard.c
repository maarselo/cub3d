/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 14:11:23 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "MLX42.h"
#include "game_internal.h"
#include <math.h>

#define MOVE_SPEED 0.2
#define PROTECTION_BUFFER 0.2

void	ft_open_door(t_data *data, mlx_key_data_t key)
{
	int		map_x;
	int		map_y;
	char	cell;

	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{
		map_x = (int)(data->player->pos_x + data->player->dir_x * 1.0);
		map_y = (int)(data->player->pos_y + data->player->dir_y * 1.0);
		if (map_x >= 0 && map_y >= 0
			&& map_x < data->map->width && map_y < data->map->height)
		{
			cell = data->map->map[map_y][map_x];
			if (cell == '_' || cell == '|')
				data->map->map[map_y][map_x] = 'O';
			else if (cell == 'O')
			{
				if (data->player->dir_x != 0)
					data->map->map[map_y][map_x] = '|';
				else
					data->map->map[map_y][map_x] = '_';
			}
		}
	}
}

void	ft_move_camera(t_data *data, mlx_key_data_t key)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = 0;
	if (key.key == MLX_KEY_LEFT)
		angle = -MOVE_SPEED;
	else if (key.key == MLX_KEY_RIGHT)
		angle = MOVE_SPEED;
	if (angle != 0)
	{
		old_dir_x = data->player->dir_x;
		old_plane_x = data->player->plane_x;
		data->player->dir_x = old_dir_x * cos(angle)
			- data->player->dir_y * sin(angle);
		data->player->dir_y = old_dir_x * sin(angle)
			+ data->player->dir_y * cos(angle);
		data->player->plane_x = old_plane_x * cos(angle)
			- data->player->plane_y * sin(angle);
		data->player->plane_y = old_plane_x * sin(angle)
			+ data->player->plane_y * cos(angle);
	}
}

void	ft_move_player(t_data *data, mlx_key_data_t key)
{
	double	move_x;
	double	move_y;
	double	total_move_x;
	double	total_move_y;

	move_x = 0;
	move_y = 0;
	total_move_x = 0;
	total_move_y = 0;
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_A
		|| key.key == MLX_KEY_D || key.key == MLX_KEY_S)
	{
		ft_calc_movement(data, key, &move_x, &move_y);
		if (move_x > 0)
			total_move_x = move_x + PROTECTION_BUFFER;
		else if (move_x != 0)
			total_move_x = move_x - PROTECTION_BUFFER;
		if (move_y > 0)
			total_move_y = move_y + PROTECTION_BUFFER;
		else if (move_y != 0)
			total_move_y = move_y - PROTECTION_BUFFER;
		ft_move_x(data, total_move_x, move_x);
		ft_move_y(data, total_move_y, move_y);
	}
}

void	ft_move(mlx_key_data_t key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx->window);
	ft_move_player(data, key);
	ft_move_camera(data, key);
	ft_open_door(data, key);
}
