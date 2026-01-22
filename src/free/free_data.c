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
#include "free.h" //stdlib.h and fre_file_contetn

void	ft_free_data(t_data *data)
{
	if (!data->colors)
		free(data->colors);
	if (data->textures)
	{
		// mlx_delete_image(data->textures->north);
		// mlx_delete_image(data->textures->south);
		// mlx_delete_image(data->textures->west);
		// mlx_delete_image(data->textures->east);
		free((data->textures));
	}
	if (data->map)
	{
		ft_free_file_content(data->map);
		free(data->map);
	}
	if (data->player)
		free(data->player);
	if (data->error)
	{
		if (data->error->is_freeable)
			free(data->error->message);
		free(data->error);
	}
	free(data);
}
