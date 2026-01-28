/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:05:38 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data struct
#include "parser.h" //struct in parser
#include "validator/map/map.h" //get_map
#include "errorctx.h" //error struct

void	ft_init_map(char *file, t_data *data)
{
	int	width;
	int	height;

	if (ft_has_error(data->error))
		return ;
	data->map->map = ft_get_map(file, data->error);
	if (!data->map->map)
		ft_set_error_system(data->error);
	ft_fill_spaces(data->map->map, data->error);
	if (ft_has_error(data->error))
		return ;
	width = 0;
	height = 0;
	while (data->map->map[0][width])
		width++;
	while (data->map->map[height])
		height++;
	data->map->height = height;
	data->map->width = width;
}
