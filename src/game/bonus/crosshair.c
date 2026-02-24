/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crosshair.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 20:33:42 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "game.h"

static void	ft_draw_horizontal_sides(t_data *data)
{
	int	i;
	int	j;

	i = WINDOW_HEIGHT / 2 - 10;
	while (i < WINDOW_HEIGHT / 2 + 10)
	{
		j = WINDOW_WIDTH / 2 - 24;
		while (j < WINDOW_WIDTH / 2 - 14)
		{
			mlx_put_pixel(data->mlx->framebuffer, j, i, 0x681e05FF);
			j++;
		}
		i++;
	}
	i = WINDOW_HEIGHT / 2 - 10;
	while (i < WINDOW_HEIGHT / 2 + 10)
	{
		j = WINDOW_WIDTH / 2 + 14;
		while (j < WINDOW_WIDTH / 2 + 24)
		{
			mlx_put_pixel(data->mlx->framebuffer, j, i, 0x681e05FF);
			j++;
		}
		i++;
	}
}

static void	ft_draw_vertical_sides(t_data *data)
{
	short	i;
	short	j;

	i = WINDOW_HEIGHT / 2 - 24;
	while (i < WINDOW_HEIGHT / 2 - 14)
	{
		j = WINDOW_WIDTH / 2 - 10;
		while (j < WINDOW_WIDTH / 2 + 10)
		{
			mlx_put_pixel(data->mlx->framebuffer, j, i, 0x681e05FF);
			j++;
		}
		i++;
	}
	i = WINDOW_HEIGHT / 2 + 14;
	while (i < WINDOW_HEIGHT / 2 + 24)
	{
		j = WINDOW_WIDTH / 2 - 10;
		while (j < WINDOW_WIDTH / 2 + 10)
		{
			mlx_put_pixel(data->mlx->framebuffer, j, i, 0x681e05FF);
			j++;
		}
		i++;
	}
}

void	ft_point(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_draw_horizontal_sides(data);
	ft_draw_vertical_sides(data);
}
