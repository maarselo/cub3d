/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 15:47:16 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "parser.h"//t_map
#include <stdlib.h> //free()

static void	ft_free_weapon_struct(t_data *data)
{
	if (data->textures->weapon->idle && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->weapon->idle);
	if (data->textures->weapon->shoot && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->weapon->shoot);
	if (data->textures->weapon->smoke && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->weapon->smoke);
	free(data->textures->weapon);
}

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
		ft_free_weapon_struct(data);
	if (data->textures->timer && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->timer);
	if (data->textures->game_over && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->game_over);
	if (data->textures->victory && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->textures->victory);
	free(data->textures);
}
