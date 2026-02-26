/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/26 13:00:19 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "parser.h"

void	ft_put_enemy_line(t_data *data, mlx_image_t *frame, int x, int y);
void	ft_get_enemy_draw_limits(t_data *data);
void	ft_set_enemy_data(t_data *data, t_enemy *curr);

void	ft_draw_enemy(t_data *data, mlx_image_t *frame)
{
	int	x;
	int	y;

	x = data->enemy_render->draw_start_x - 1;
	while (++x < data->enemy_render->draw_end_x)
	{
		data->enemy_render->tex_x = (int)((x - (data->enemy_render->screen_x
						- data->enemy_render->size / 2)) * frame->width
				/ data->enemy_render->size);
		if (data->enemy_render->trans_y > 0 && x >= 0 && x < WINDOW_WIDTH
			&& data->enemy_render->trans_y < data->mlx->z_buffer[x])
		{
			y = data->enemy_render->draw_start_y - 1;
			while (++y < data->enemy_render->draw_end_y)
				ft_put_enemy_line(data, frame, x, y);
		}
	}
}

mlx_image_t	*ft_update_enemy_frame(t_data *data, t_enemy *curr,
		bool should_change_frame)
{
	mlx_image_t	*frame;

	if (should_change_frame)
	{
		if (curr->frame == 1)
			curr->frame = 2;
		else if (curr->frame == 2)
			curr->frame = 1;
	}
	if (curr->frame == 1)
		frame = data->enemies->enemy_frame1;
	else if (curr->frame == 2)
		frame = data->enemies->enemy_frame2;
	return (frame);
}

t_enemy	*ft_skip_enemy(t_enemy *enemy)
{
	if (enemy->is_dead)
		enemy = enemy->next;
	return (enemy);
}

void	ft_draw_enemies(t_data *data)
{
	t_enemy		*curr;
	mlx_image_t	*frame;
	static int	counter;
	bool		should_change_frame;

	should_change_frame = false;
	counter++;
	if (counter >= 15)
	{
		should_change_frame = true;
		counter = 0;
	}
	curr = data->enemies->enemies;
	while (curr)
	{
		if (curr->is_dead)
		{
			curr = curr->next;
			continue ;
		}
		frame = ft_update_enemy_frame(data, curr, should_change_frame);
		curr = ft_skip_enemy(curr);
		ft_set_enemy_data(data, curr);
		ft_get_enemy_draw_limits(data);
		ft_draw_enemy(data, frame);
		curr = curr->next;
	}
}
