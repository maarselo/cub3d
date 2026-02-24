/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 19:39:23 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include "errorctx.h"

# define MINIMAP_SIDE	250
# define MINIMAP_MARGE	40
# define BLOCKS_VIEW	7

void	ft_init_minimap(t_data *data)
{
	if (ft_has_error(data->error))
		return ;
	data->minimap->start_x = MINIMAP_MARGE;
	data->minimap->start_y = WINDOW_HEIGHT - MINIMAP_SIDE - MINIMAP_MARGE;
	data->minimap->final_x = MINIMAP_SIDE + MINIMAP_MARGE;
	data->minimap->final_y = WINDOW_HEIGHT - MINIMAP_MARGE;
	data->minimap->center_x = (MINIMAP_SIDE / 2) + MINIMAP_MARGE;
	data->minimap->center_y = WINDOW_HEIGHT - (MINIMAP_SIDE / 2) - MINIMAP_MARGE;
	data->minimap->tile_size = MINIMAP_SIDE / BLOCKS_VIEW;
	data->minimap->relation_x = 0;
	data->minimap->relation_y = 0;
}
