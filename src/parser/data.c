/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 20:47:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include <unistd.h> //NULL
#include "libft.h" //ft_calloc
#include "errorctx.h" //ft_set_error
#include "parser.h" //struct in parser
#include "free.h"//ft_free_data

static void	ft_init_structs_utils(t_data *data, t_error *error)
{
	data->colors = (t_colors *)ft_calloc(1, sizeof(t_colors));
	if (!data->colors)
		return (ft_set_error_system(error));
	data->textures = (t_textures *)ft_calloc(1, sizeof(t_textures));
	if (!data->textures)
		return (ft_set_error_system(error));
	data->textures->door = (t_door *)ft_calloc(1, sizeof(t_door));
	if (!data->textures->door)
		return (ft_set_error_system(error));
	data->textures->weapon = (t_weapon *)ft_calloc(1, sizeof(t_weapon));
	if (!data->textures->weapon)
		return (ft_set_error_system(error));
	data->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!data->map)
		return (ft_set_error_system(error));
	data->player = (t_player *)ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (ft_set_error_system(error));
	data->mlx = (t_mlx *)ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx)
		return (ft_set_error_system(error));
}

t_data	*ft_init_data(t_error *error)
{
	t_data	*data;

	if (ft_has_error(error))
		return (NULL);
	data = (t_data *)ft_calloc(1, (sizeof(t_data)));
	if (!data)
		return (ft_set_error_system(error), NULL);
	ft_init_structs_utils(data, error);
	return (data);
}
