/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 21:04:51 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include <math.h>

#define SENSIBILITY 0.003

void	ft_mouse(double x, double y, void *param)
{
	double			delta;
	double			rotation;
	double			tmp_x;
	t_data			*data;
	static double	old_x;

	(void)y;
	data = (t_data *)param;
	if (!old_x)
	{
		old_x = x;
		return ;
	}
	delta = x - old_x;
	rotation = delta * SENSIBILITY;
	tmp_x = data->player->dir_x;
	data->player->dir_x = tmp_x * cos(rotation) - data->player->dir_y * sin(rotation);
	data->player->dir_y = tmp_x * sin(rotation) + data->player->dir_y * cos(rotation);
	tmp_x = data->player->plane_x;
	data->player->plane_x = tmp_x * cos(rotation) - data->player->plane_y * sin(rotation);
	data->player->plane_y = tmp_x * sin(rotation) + data->player->plane_y * cos(rotation);
	old_x = x;
}
