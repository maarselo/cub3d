/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 13:21:27 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include <math.h>

void	ft_move(mlx_key_data_t key, void *param)
{
	t_data	*data;
	double	speed;
	double	buffer;
	double	move_x;
	double	move_y;
	double	total_move_x;
	double	total_move_y;

	data = (t_data *)param;
	speed = 0.2;
	buffer = 0.2; //change this
	move_x = 0;
	move_y = 0;
	total_move_x = 0;
	total_move_y = 0;
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx->window);
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_A || key.key == MLX_KEY_D || key.key == MLX_KEY_S)
	{
		//Se calcula el total del movimiento
		if (key.key == MLX_KEY_W)
		{
			move_x = data->player->dir_x * speed;
			move_y = data->player->dir_y * speed;
		}
		//Se hace -data porque la tecla S va para atras de donde apuntamos
		if (key.key == MLX_KEY_S)
		{
			move_x = -data->player->dir_x * speed;
			move_y = -data->player->dir_y * speed;
		}
		//Se usa plan porque es horizontal y el valor es de nuestro hombro a la derecha es +1, por eso A = izquierda(-1) y D normal
		if (key.key == MLX_KEY_A)
		{
			move_x = -data->player->plane_x * speed;
			move_y = -data->player->plane_y *speed;
		}
		if (key.key == MLX_KEY_D)
		{
			move_x = data->player->plane_x * speed;
			move_y = data->player->plane_y * speed;
		}
		//Porque hay que sumar buffer a la direccion a la que vayamos porque hace de escudo,
		if (move_x > 0)
			total_move_x = move_x + buffer;
		else
			total_move_x = move_x - buffer;
		if (move_y > 0)
			total_move_y = move_y + buffer;
		else
			total_move_y = move_y - buffer;
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + total_move_x)] != '1' &&
			data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + total_move_x)] != '_' && 
			data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + total_move_x)] != '|')
			data->player->pos_x += move_x;
		if (data->map->map[(int)(data->player->pos_y + total_move_y)][(int)data->player->pos_x] != '1' &&
			data->map->map[(int)(data->player->pos_y + total_move_y)][(int)data->player->pos_x] != '_' &&
			data->map->map[(int)(data->player->pos_y + total_move_y)][(int)data->player->pos_x] != '|')
			data->player->pos_y += move_y;
	}
	double	old_dir_x;
	double	old_plane_x;
	if (key.key == MLX_KEY_LEFT)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = old_dir_x * cos(-speed) - data->player->dir_y * sin(-speed);
		data->player->dir_y = old_dir_x * sin(-speed) + data->player->dir_y * cos(-speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = old_plane_x * cos(-speed) - data->player->plane_y * sin(-speed);
		data->player->plane_y = old_plane_x * sin(-speed) + data->player->plane_y * cos(-speed);
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = old_dir_x * cos(speed) - data->player->dir_y * sin(speed);
		data->player->dir_y = old_dir_x * sin(speed) + data->player->dir_y * cos(speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = old_plane_x * cos(speed) - data->player->plane_y * sin(speed);
		data->player->plane_y = old_plane_x * sin(speed) + data->player->plane_y * cos(speed);
	}

	int		map_x;
	int		map_y;
	char	cell;
	
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{	
		map_x = (int)(data->player->pos_x + data->player->dir_x * 1.0);
		map_y = (int)(data->player->pos_y + data->player->dir_y * 1.0);
		if (map_x >= 0 && map_y >= 0 && map_x < data->map->width && map_y < data->map->height)
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
