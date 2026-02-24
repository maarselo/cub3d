/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 16:31:58 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "MLX42.h" //delete to free_some_mlx_structs
#include "free.h" //fre_file_contetn
#include <stdlib.h> //free()
#include "parser.h"//t_map
#include "errorctx.h" //free_terror

void	ft_free_texture_struct(t_data *data);
void	ft_free_enemies_struct(t_data *data);
void	ft_free_map_struct(t_data *data);
void	ft_free_mlx_struct(t_data *data);
void	ft_free_error_struct(t_data *data);

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->colors)
		free(data->colors);
	if (data->textures)
		ft_free_texture_struct(data);
	if (data->map)
		ft_free_map_struct(data);
	if (data->enemies)
		ft_free_enemies_struct(data);
	if (data->player)
		free(data->player);
	if (data->minimap)
		free(data->minimap);
	if (data->mlx)
		ft_free_mlx_struct(data);
	if (data->error)
		ft_free_error_struct(data);
	free(data);
}
