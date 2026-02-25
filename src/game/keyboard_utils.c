/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 14:09:25 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "MLX42.h"

#define MOVE_SPEED 0.2

void	ft_move_x(t_data *data, double total_move_x, double move_x)
{
	double	new_pos_x;

	new_pos_x = data->player->pos_x + total_move_x;
	if (data->map->map[(int)data->player->pos_y][(int)new_pos_x] != '1' &&
		data->map->map[(int)data->player->pos_y][(int)new_pos_x] != '_' &&
		data->map->map[(int)data->player->pos_y][(int)new_pos_x] != '|')
		data->player->pos_x += move_x;
}

void	ft_move_y(t_data *data, double total_move_y, double move_y)
{
	double	new_pos_y;

	new_pos_y = data->player->pos_y + total_move_y;
	if (data->map->map[(int)new_pos_y][(int)data->player->pos_x] != '1' &&
		data->map->map[(int)new_pos_y][(int)data->player->pos_x] != '_' &&
		data->map->map[(int)new_pos_y][(int)data->player->pos_x] != '|')
		data->player->pos_y += move_y;
}

void	ft_calc_movement(t_data *data, mlx_key_data_t key,
			double *move_x, double *move_y)
{
	if (key.key == MLX_KEY_W)
	{
		(*move_x) = data->player->dir_x * MOVE_SPEED;
		(*move_y) = data->player->dir_y * MOVE_SPEED;
	}
	if (key.key == MLX_KEY_S)
	{
		(*move_x) = -data->player->dir_x * MOVE_SPEED;
		(*move_y) = -data->player->dir_y * MOVE_SPEED;
	}
	if (key.key == MLX_KEY_A)
	{
		(*move_x) = -data->player->plane_x * MOVE_SPEED;
		(*move_y) = -data->player->plane_y * MOVE_SPEED;
	}
	if (key.key == MLX_KEY_D)
	{
		(*move_x) = data->player->plane_x * MOVE_SPEED;
		(*move_y) = data->player->plane_y * MOVE_SPEED;
	}
}
