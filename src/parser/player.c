/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/29 17:35:53 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data struct
#include "parser.h" //struct in parser
#include "errorctx.h" //error struct
#include "libft.h" //ft_isaplha
#include "cub3d.h" //t_data struct

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
			if (ft_isalpha(data->map->map[i][j]))
			{
				data->player->pos_x = (double)j + 0.5;
				data->player->pos_y = (double)i + 0.5;
				if (data->map->map[i][j] == 'N')
					data->player->orientation = NORTH;
				else if (data->map->map[i][j] == 'S')
					data->player->orientation = SOUTH;
				else if (data->map->map[i][j] == 'W')
					data->player->orientation = WEST;
				else
					data->player->orientation = EAST;
			}
	}
}
