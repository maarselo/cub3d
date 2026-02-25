/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 13:25:18 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "game.h"
#include <math.h>

#define WEAPONG_RANGE 0.1

#define IDLE 0
#define SHOOT 1
#define SMOKE 2

static void	ft_change_frame(int frame_update, int *frame_counter, t_data *data)
{
	if (frame_update == SHOOT)
	{
		data->textures->weapon->idle->enabled = false;
		data->textures->weapon->shoot->enabled = true;
		(*frame_counter)++;
	}
	else if (frame_update == SMOKE)
	{
		data->textures->weapon->shoot->enabled = false;
		data->textures->weapon->smoke->enabled = true;
		*frame_counter = 0;
	}
	else if (frame_update == IDLE)
	{
		data->textures->weapon->is_shooting = false;
		data->textures->weapon->smoke->enabled = false;
		data->textures->weapon->idle->enabled = true;
		(*frame_counter)++;
	}
}

void	ft_update_animation(void *param)
{
	t_data		*data;
	static int	counter;
	static int	frame;

	data = (t_data *)param;
	if (!data->textures->weapon->is_shooting)
	{
		frame = SHOOT;
		return ;
	}
	counter++;
	if (counter >= 4)
	{
		if (frame == SHOOT)
			ft_change_frame(SHOOT, &frame, data);
		else if (frame == SMOKE)
			ft_change_frame(SMOKE, &frame, data);
		else
			ft_change_frame(IDLE, &frame, data);
		counter = 0;
	}
}

static bool	ft_check_impact_enemy(double row, double col, t_data *data)
{
	double	result_x;
	double	result_y;
	t_enemy	*current_enemy;

	current_enemy = data->enemies->enemies;
	while (current_enemy)
	{
		result_x = fabs(col - current_enemy->pos_x);
		result_y = fabs(row - current_enemy->pos_y);
		if (result_x <= WEAPONG_RANGE && result_y <= WEAPONG_RANGE)
		{
			current_enemy->is_died = true;
			data->map->map[(int)current_enemy->pos_y]
			[(int)current_enemy->pos_x] = '0';
			--data->enemies->total_enemies;
			return (true);
		}
		current_enemy = current_enemy->next;
	}
	return (false);
}

static bool	ft_is_valid_shoot(int bullet_x, int bullet_y, t_data *data)
{
	if (bullet_x < 0 || (int)bullet_x >= data->map->width
		|| bullet_y < 0 || bullet_y >= data->map->height)
		return (false);
	if (data->map->map[bullet_y][bullet_x] != 'e'
		&& data->map->map[bullet_y][bullet_x] != '0'
		&& data->map->map[bullet_y][bullet_x] != 'O')
		return (false);
	return (true);
}

void	ft_shoot(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_data		*data;
	double		bullet_x;
	double		bullet_y;
	double		distance;

	(void)mods;
	data = (t_data *)param;
	distance = 0.0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS
		&& !data->textures->weapon->is_shooting)
	{
		data->textures->weapon->is_shooting = true;
		while (distance <= 2.5)
		{
			bullet_x = data->player->pos_x + data->player->dir_x * distance;
			bullet_y = data->player->pos_y + data->player->dir_y * distance;
			if (!ft_is_valid_shoot(bullet_x, bullet_y, data))
				break ;
			if (ft_check_impact_enemy(bullet_y, bullet_x, data))
				return ;
			distance += 0.009;
		}
	}
}
