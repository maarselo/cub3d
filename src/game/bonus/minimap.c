/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 19:47:58 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "parser.h" //t_data
#include "game.h" //Macros WINDOWHEIGT and more
#include <math.h> ///flood

# define RED 0xFF0000FF
# define WHITE 0xFFFFFFFF
# define GREY 0x333333FF
# define BLACK 0x000000FF

#define PLAYER_SIDE 8  //draw_player 

#define RAY_LENGTH 40 //the length of  the
#define FOV_RAYS_SEPARATION 0.04 //separation of the rays in the fov

static void	ft_draw_player(t_data *data)
{
	int init_col;
	int final_col;
	int init_row;
	int final_row;
	int current_col;

	init_col = data->minimap->center_x - (PLAYER_SIDE / 2); //Se sma porque ahor alo quermeos mas a la derecha
	final_col = data->minimap->center_x + (PLAYER_SIDE / 2); //Se sma porque ahor alo quermeos mas a la derecha
	init_row = data->minimap->center_y - (PLAYER_SIDE / 2); //Se resta minimap borde proque siempre lo quremoe mas arriba
	final_row = data->minimap->center_y + (PLAYER_SIDE / 2); //Se resta minimap borde proque siempre lo quremoe mas arriba
	while (init_row++ <= final_row)
	{
		current_col = init_col;
		while (current_col++ <= final_col)
			mlx_put_pixel(data->mlx->framebuffer, current_col, init_row, RED);
	}
}
static void ft_draw_fov(t_data *data)
{
	int		i;
	double	column;
	double	ray_x;
	double	ray_y;

	column = -1.0;
	while (column <= 1.0)
	{
		ray_x = data->player->dir_x + data->player->plane_x * column;
		ray_y = data->player->dir_y + data->player->plane_y * column;
		i = -1;
		while (++i < RAY_LENGTH)
			mlx_put_pixel(data->mlx->framebuffer,
				data->minimap->center_x + (ray_x * i),
				data->minimap->center_y + (ray_y * i), RED);
		column += FOV_RAYS_SEPARATION;
	}
}

void	ft_draw_pixel_by_type(int pixel_col, int pixel_row, t_data *data)
{
	if (data->minimap->relation_x < 0 || data->minimap->relation_y < 0
		|| data->minimap->relation_x >= data->map->width
		|| data->minimap->relation_y >= data->map->height
		|| data->map->map[data->minimap->relation_y]
		[data->minimap->relation_x] == '1')
		mlx_put_pixel(data->mlx->framebuffer, pixel_col, pixel_row, BLACK);
	else if (data->map->map[data->minimap->relation_y]
		[data->minimap->relation_x] == '_'
		|| data->map->map[data->minimap->relation_y]
		[data->minimap->relation_x] == '|')
		mlx_put_pixel(data->mlx->framebuffer, pixel_col, pixel_row, GREY);
	else if (data->map->map[data->minimap->relation_y]
		[data->minimap->relation_x] == 'e')
		mlx_put_pixel(data->mlx->framebuffer, pixel_col, pixel_row, RED);
	else
		mlx_put_pixel(data->mlx->framebuffer, pixel_col, pixel_row, WHITE);
}

void ft_minimap(void *param)
{
	int 	pixel_row;
	int 	pixel_col;
	double 	rel_x;
	double 	rel_y;
	t_data	*data;

	data = (t_data *)param;
	pixel_row = data->minimap->start_y;
	while (pixel_row++ < data->minimap->final_y)
	{
		pixel_col = data->minimap->start_x;
		while (pixel_col++ < data->minimap->final_x)
		{
			rel_x = (double)(pixel_col - data->minimap->center_x) / data->minimap->tile_size;
			rel_y = (double)(pixel_row - data->minimap->center_y) / data->minimap->tile_size;
			data->minimap->relation_x = (int)floor(data->player->pos_x + rel_x);
			data->minimap->relation_y = (int)floor(data->player->pos_y + rel_y);
			ft_draw_pixel_by_type(pixel_col, pixel_row, data);
		}
	}
	ft_draw_player(data);
	ft_draw_fov(data);
}
