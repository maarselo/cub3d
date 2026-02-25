/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_struct.c                                   :+:      :+:    :+:   */
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

static void	ft_free_enemy_linked_list(t_enemies *enemies)
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

void	ft_free_enemies_struct(t_data *data)
{
	if (data->enemies->enemies)
		ft_free_enemy_linked_list(data->enemies);
	if (data->enemies->enemy_frame1 && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->enemies->enemy_frame1);
	if (data->enemies->enemy_frame2 && mlx_errno != MLX_INVPNG)
		mlx_delete_image(data->mlx->window, data->enemies->enemy_frame2);
	free(data->enemies);
	data->enemies = NULL;
}
