/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 12:25:50 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include <math.h>

#define COLLISION_DIE 0.3

void	ft_check_position(void *param)
{
	double	result_y;
	double	result_x;
	t_data	*data;
	t_enemy	*current_enemy;
	
	data = (t_data *)param;
	if (data->enemies->total_enemies == 0)
		return ;
	current_enemy = data->enemies->enemies;
	while (current_enemy)
	{
		if (current_enemy->is_died)
		{
			current_enemy = current_enemy->next;
			continue ;
		}
		result_x = fabs(data->player->pos_x - current_enemy->pos_x);
		result_y = fabs(data->player->pos_y - current_enemy->pos_y);
		if (result_x <= COLLISION_DIE && result_y < COLLISION_DIE)
		{
			//flag u sistema de termnate 
			mlx_close_window(data->mlx->window);
		}
		current_enemy = current_enemy->next;
	}
}
