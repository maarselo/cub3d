/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 14:56:55 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include <math.h>

#define COLLISION_DIE 0.3

void	ft_monitor_player_death(t_data *data)
{
	double	result_y;
	double	result_x;
	t_enemy	*current_enemy;

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
			data->game_over = true;
		current_enemy = current_enemy->next;
	}
}
