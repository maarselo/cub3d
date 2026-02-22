/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "MLX42.h" //delete to free_some_mlx_structs
#include "free.h" //fre_file_contetn
#include <stdlib.h> //free()
#include "parser.h"//t_map
#include "errorctx.h" //free_terror

void	ft_free_enemy_linked_list(t_enemies *enemies)
{
	t_enemy	*tmp;
	t_enemy	*next_node;

	tmp = enemies->enemies;
	while (tmp)
	{
		next_node = tmp->next;
		free(tmp);
		tmp = next_node;
	}
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->colors)
		free(data->colors);
	if (data->textures)
	{
		if (data->textures->north && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->north);
		if (data->textures->south && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->south);
		if (data->textures->west && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->west);
		if (data->textures->east && mlx_errno != MLX_INVPNG)
			mlx_delete_image(data->mlx->window, data->textures->east);
		if (data->textures->door)
			mlx_delete_image(data->mlx->window, data->textures->door);
		if (data->textures->weapon)
		{
			if (data->textures->weapon->idle)
				mlx_delete_image(data->mlx->window, data->textures->weapon->idle);
			if (data->textures->weapon->shoot)
				mlx_delete_image(data->mlx->window, data->textures->weapon->shoot);
			if (data->textures->weapon->smoke)
				mlx_delete_image(data->mlx->window, data->textures->weapon->smoke);
			free(data->textures->weapon);
		}
		if (data->textures->timer)
			mlx_delete_image(data->mlx->window, data->textures->timer);
		if (data->textures->date)
			mlx_delete_image(data->mlx->window, data->textures->date);
		free(data->textures);
	}
	if (data->map)
	{
		if (data->map->map)
			ft_free_file_content(data->map->map);
		free(data->map);
	}
	if (data->enemies)
	{
		if (data->enemies->enemies)
		{
			ft_free_enemy_linked_list(data->enemies);
			data->enemies->enemies = NULL;
		}
		free(data->enemies);
	}
	if (data->player)
		free(data->player);
	if(data->mlx)
	{
		if (data->mlx->window)
			mlx_terminate(data->mlx->window);
		free(data->mlx);
	}
	if (data->error)
	{
		if (data->error->is_freeable)
			free(data->error->message);
		free(data->error);
	}
	free(data);
}
