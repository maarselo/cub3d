/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:57 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 13:30:21 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"
#include <math.h>
#include "game_internal.h"

void	ft_render(void *param)
{
	int		current_col; // current pixel column of the screen
	double	camera_x; // used to calculate in which side of the screen is current_col
	double	ray_dir_x; // direction of the ray casted on x axis
	double	ray_dir_y; // direction of the ray casted on y axis
	double	delta_dist_x; // how many pixels it takes for the ray to cross 1 whole x unit (vertical lines)
	double	delta_dist_y; // how many pixels it takes for the ray to cross 1 whole y unit (horizontal lines)
	double	side_dist_x; // distance to first vertical line
	double	side_dist_y; // distance to first horizontal line
	int		map_x; // player pos_x casted to int
	int		map_y; // player pos_y casted to int
	int		step_x; // used to know in which direction the player is going in the x axis
	int		step_y; // used to know in which direction the player is going in the y axis
	bool	hit; // used to knw if the ray hit a wall
	int		side; // to know if the ray passed a vertical or horizontal line first (0 vertical x 1 horizontal y)
	double	perpendicular_dist; // straight distance to the wall (avoid fisheye)
	int		wall_height; // how tall the wall looks on the screen
	int		draw_start; // point where you start to draw the wall
	int		draw_end; // point where you stop drawing the wall
	mlx_image_t	*wall_texture;
	double	wall_x; // in what x pixel of the wall the ray collides
	int		tex_x; // x pixel (col) of the image wall_x represents
	double	step; // how many pixels to skip, to resize the image
	double	tex_pos; // initial position of the texture to draw
	t_data	*data;

	data = (t_data *)param;
	current_col = -1;
	while (++current_col < WINDOW_WIDTH)
	{
		wall_texture = NULL;
		camera_x = 2 * current_col / (double)WINDOW_WIDTH - 1; //calculas columna actual -1 - +1.(0-1920)
		ray_dir_x = data->player->dir_x + (data->player->plane_x * camera_x); //te dicen hacia dónde estás mirando exactamente para esa columna de la pantalla.
		ray_dir_y = data->player->dir_y + (data->player->plane_y * camera_x); //te dicen hacia dónde estás mirando exactamente para esa columna de la pantalla.
		map_x = (int)data->player->pos_x;
		map_y = (int)data->player->pos_y;
		if (ray_dir_x != 0)
			delta_dist_x = fabs(1 / ray_dir_x); //Se calcula despues de la primera linea, cuanto es para la sig horizontal
		else //solo en caso que el rayo sea del del medio
			delta_dist_x = 1e30;
		if (ray_dir_y != 0)
			delta_dist_y = fabs(1 / ray_dir_y); //Se calcula despes de la primer alinea, cuanto es para la sig vertical
		else //solo en caso para cero
			delta_dist_y = 1e30; 
		if (ray_dir_x < 0)
		{
			step_x = -1; //Si va a la izquiera el rayo
			side_dist_x = (data->player->pos_x - map_x) * delta_dist_x; //calcula distnacia  apriemr alinea horizontal
		}
		else
		{
			step_x = 1;  //Si va a la derecha el rayo
			side_dist_x = (map_x + 1.0 - data->player->pos_x) * delta_dist_x; //calcula distnacia  apriemr alinea horizontal
		}
		if (ray_dir_y < 0)
		{
			step_y = -1; //Si va para arriba el rayo 
			side_dist_y = (data->player->pos_y - map_y) * delta_dist_y; //calcula distancia a primera linea vertical
		}
		else
		{
			step_y = 1; //Si va para abajo el rayo
			side_dist_y = (map_y + 1.0 - data->player->pos_y) * delta_dist_y; //calcula distancia a primera linea vertical
		}
		hit = false;
		while (!hit)
		{
			if (side_dist_x < side_dist_y)  //Si es menor a distancia al primer rato verticla
			{
				side_dist_x += delta_dist_x; //actualiamos valor a la siugiente linea vertica
				map_x += step_x; //Usamos para seguir la direccion a la que apuntamos
				side = 0;  //chocamos con una linea vertical
			} 
			else //Si es menor a distancia al primer rato horizontal
			{
				side_dist_y += delta_dist_y; //actualizamos valor a ls isugiente linea horizontal
				map_y += step_y; //Usamos para seguir la direccion a la que apuntamos
				side = 1;  //chocamos con una line horizontal
			}
			if (data->map->map[map_y][map_x] == '1') //comrpobamos que hemos llegado al final dela vista(muro)
				hit = true;
			else if (data->map->map[map_y][map_x] == '_' || data->map->map[map_y][map_x] == '|') //Si he chocado con una puerta
			{
				hit = true;
				wall_texture = data->textures->door;
			}
		}
		if (side == 0)
		{
			perpendicular_dist = side_dist_x - delta_dist_x; //perpendicular_dist es realmente side_dist_x pero restandole el ultio incremento
			wall_x = data->player->pos_y + ray_dir_y * perpendicular_dist;
		}
		else
		{
			perpendicular_dist = side_dist_y - delta_dist_y; //perpendicular_dist es realmente side_dist_y pero restandole el ultio incremento
			wall_x = data->player->pos_x + ray_dir_x * perpendicular_dist;
		}
		wall_x -= floor(wall_x);
		wall_height = (int)(WINDOW_HEIGHT / perpendicular_dist); //altura  dee la pared a lo lejos o cerca
		draw_start = (WINDOW_HEIGHT - wall_height) / 2; //donde se ha de iniciar el dibujo de la pared
		draw_end = draw_start + wall_height; //donde parar el diujo de la pred
		if (draw_start < 0) //proteger si en estas al lado dde la pared y que no pinte en -abajo de pantalla
			draw_start = 0;
		if (draw_end >= WINDOW_HEIGHT) //proteger que n estes al lado de la parex y pinta +arriba de pantalla
			draw_end = WINDOW_HEIGHT - 1;
		if (!wall_texture) //Si no es una puerta
		{
			if (side == 0) //si se ha chocado con una pared vertical y no ha sido ninguna puerta
			{
				if (step_x == -1)
					wall_texture = data->textures->east; //Depende de donde aunte el rayo
				else 
					wall_texture = data->textures->west; //Depende de donde aunte el rayo
			}
			else//si se ha chocado con una pared horizontal y no ha sido ninnguna puerta
			{
			if (step_y == -1)
				wall_texture = data->textures->south; //Depende de donde aunte el rayo
			else
				wall_texture = data->textures->north;//Depende de donde aunte el rayo
			}
		}
		tex_x = (int)((double)wall_texture->width * wall_x); //columna actual para printar sus pixeles
		step = (double)wall_texture->height / wall_height; //Calcular si la foto no se ve completa, cuantos pixeles ha de saltar para pasar al siguiente
		tex_pos = (draw_start - WINDOW_HEIGHT / 2 + wall_height / 2) * step; //posisicon principal para empezar a printar la pared, protege de en caso ver toda una pared con zoom empezar del medio
		int	i = 0;
		while (i < draw_start) //pintar suelo
		{
			mlx_put_pixel(data->mlx->framebuffer, current_col, i, data->colors->floor);
			i++;
		}
		while (i < draw_end) //pintar pared
		{
			int	pixel = ft_get_pixel((int)tex_pos, tex_x, wall_texture); //Coger el pixel exacto y pasarlo a uint32_t
			mlx_put_pixel(data->mlx->framebuffer, current_col, i, pixel);
			tex_pos += step;
			i++;
		}
		while (i < WINDOW_HEIGHT) //pintar cielo
		{
			mlx_put_pixel(data->mlx->framebuffer, current_col, i, data->colors->ceiling);
			i++;
		}
		data->mlx->z_buffer[current_col] = perpendicular_dist;
	}
}
