/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "parser.h"//t_map
#include <stdlib.h> //free()

void	ft_free_texture_struct(t_data *data)
{
	if (data->textures->north && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->north);
	if (data->textures->south && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->south);
	if (data->textures->west && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->west);
	if (data->textures->east && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->east);
	if (data->textures->door && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->door);
	if (data->textures->weapon)
	{
		if (data->textures->weapon->idle && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->weapon->idle);
		if (data->textures->weapon->shoot && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->weapon->shoot);
		if (data->textures->weapon->smoke && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->weapon->smoke);
		free(data->textures->weapon);
	}
	if (data->textures->timer && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->timer);
	if (data->textures->date && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->date);
	free(data->textures);
}
