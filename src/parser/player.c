/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/29 20:28:31 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data struct
#include "parser.h" //struct in parser
#include "errorctx.h" //error struct
#include "cub3d.h" //t_data struct

static bool	ft_is_start_position(int c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static void	ft_set_player_cfg(int x, int y, t_data *data)
{
	data->player->pos_x = (double)x + 0.5;
	data->player->pos_y = (double)y + 0.5;
	if (data->map->map[y][x] == 'N')
	{
		data->player->dir_x = 0;
		data->player->dir_y = -1;
		data->player->plane_x = 1;
		data->player->plane_y = 0;
	}
	else if (data->map->map[y][x] == 'S')
	{
		data->player->dir_x = 0;
		data->player->dir_y = 1;
		data->player->plane_x = -1;
		data->player->plane_y = 0;
	}
	else if (data->map->map[y][x] == 'W')
	{
		data->player->dir_x = -1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = -1;
	}
	else
	{
		data->player->dir_x = 1;
		data->player->dir_y = 0;
		data->player->plane_x = 0;
		data->player->plane_y = 1;
	}
}

void	ft_init_player(t_data *data)
{
	int	i;
	int	j;

	if (ft_has_error(data->error))
		return ;
	i = -1;
	while (data->map->map[++i])
	{
		j = -1;
		while (data->map->map[i][++j])
			if (ft_is_start_position(data->map->map[i][j]))
				ft_set_player_cfg(j, i, data);
	}
}
