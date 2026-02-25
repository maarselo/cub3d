/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 13:19:22 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>
#include "parser.h"
#include "../game_internal.h"

void	ft_draw_enemies(void *param)
{
	t_data	*data;
	t_enemy	*curr;
	double	sprite_x;// posicion del enemigo respecto a ti en x
	double	sprite_y;// posicion del enemigo respecto a ti en y
	double	trans_x;// posicion del enemigo en tu pantalla relativo a tu centro de vision en x (profundidad)
	double	trans_y;// posicion del enemigo en tu pantalla relativo a tu centro de vision en y (profundidad)
	double	inverse_det;// parecido a camara x, para pasar de un mapa 2d a una camara
	double	screen_x;// posicion en la pantalla del enemigo (si esta en el centro 0, izq -1, der 1)
	double	size;// size del enemigo
	int		draw_start_x;// posicion inicial donde empezar a pintar al enemigo en x
	int		draw_end_x;// posicion final donde pintar al enemigo en x
	int		draw_start_y;// posicion inicial donde empezar a pintar al enemigo en y
	int		draw_end_y;// posicion final donde pintar al enemigo en y
	int		tex_x;// que pixel de la imagen corresponde a que pixel de la pantalla en x
	int		tex_y;// que pixel de la imagen corresponde a que pixel de la pantalla en y
	int		x;
	int		y;
	int		d;// distancia des del pixel actual de la pantalla hasta el inicio del sprite
	uint32_t	color;
	mlx_image_t	*frame; ///////////////////
	static int	counter; ///////////////////////
	bool		should_change_frame;/////////////////

	data = (t_data *)param;
	should_change_frame = false;///////////////
	counter++; ////////////////
	if (counter >= 15) ////////////
	{ ////////////
		should_change_frame = true;///////////////
		counter = 0; ////////////
	} ////////////
	curr = data->enemies->enemies;
	while (curr)
	{
		if (should_change_frame)//////////
		{////////////
			if (curr->frame == 1)////////////////
				curr->frame = 2;/////////////////////////
			else if (curr->frame == 2)/////////////////////////
				curr->frame = 1;/////////////////////////
		}//////////
		if (curr->frame == 1)///////
			frame = data->enemies->enemy_frame1;//////
		else if (curr->frame == 2)///////
			frame = data->enemies->enemy_frame2;/////////
		if (curr->is_died)/////////////////////////
		{/////////////////////////
			curr = curr->next;/////////////////////////
			continue ;/////////////////////////
		}/////////
		sprite_x = curr->pos_x - data->player->pos_x;
		sprite_y = curr->pos_y - data->player->pos_y;
		inverse_det = 1 / (data->player->plane_x * data->player->dir_y - data->player->dir_x * data->player->plane_y);
		trans_x = inverse_det * (data->player->dir_y * sprite_x - data->player->dir_x * sprite_y);
		trans_y = inverse_det * (-data->player->plane_y * sprite_x + data->player->plane_x * sprite_y);
		screen_x = (WINDOW_WIDTH / 2) * (1 + trans_x / trans_y);
		size = fabs((WINDOW_HEIGHT / trans_y) / 1.5);
		draw_end_y = (size / 2) + (WINDOW_HEIGHT / 2) + (int)(175.0 / trans_y);
		draw_start_y = draw_end_y - size;
		if (draw_start_y < 0)
			draw_start_y = 0;
		if (draw_end_y >= WINDOW_HEIGHT)
			draw_end_y = WINDOW_HEIGHT - 1;
		draw_start_x = -(size / 2) + screen_x;
		draw_end_x = (size / 2) + screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		if (draw_end_x >= WINDOW_WIDTH)
			draw_end_x = WINDOW_WIDTH - 1;
		x = draw_start_x - 1;
		while (++x < draw_end_x)
		{
			tex_x = (int)((x - (screen_x - size / 2)) * frame->width / size);
			if (trans_y > 0 && x >= 0 && x < WINDOW_WIDTH && trans_y < data->mlx->z_buffer[x])
			{
				y = draw_start_y - 1;
				while (++y < draw_end_y)
				{
					d = (y - (int)(175.0 / trans_y)) * 256 - WINDOW_HEIGHT * 128 + size * 128;
					tex_y = ((d * frame->height) / size) / 256;
					color = ft_get_pixel(tex_y, tex_x, frame);
					if ((color & 0x000000FF) != 0)
						mlx_put_pixel(data->mlx->framebuffer, x, y, color);
				}
			}
		}
		curr = curr->next;
	}
}
