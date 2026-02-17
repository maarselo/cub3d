/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/10 19:46:48 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "errorctx.h"
#include "game.h"
#include <math.h>

uint32_t	ft_get_pixel(mlx_image_t *texture, int col, int row)
{
	if ((uint32_t)col >= texture->width || (uint32_t)row >= texture->height || col < 0 || row < 0)
		return (0);
	uint32_t	pos = (row * texture->width + col) * 4;
	uint8_t r = texture->pixels[pos];
	uint8_t g = texture->pixels[pos + 1];
	uint8_t b = texture->pixels[pos + 2];
	uint8_t a = texture->pixels[pos + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

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
	while (current_col++ < WINDOW_WIDTH)
	{
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
			if (data->map->map[map_y][map_x] == '1' || data->map->map[map_y][map_x] == '_' || data->map->map[map_y][map_x] == '|') //comrpobamos que hemos llegado al final dela vista(muro)
				hit = true;
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
		if (side == 0) //si se ha chocado con una pared vertical
		{
			if (step_x == -1)
				wall_texture = data->textures->east; //Depende de donde aunte el rayo
			else 
				wall_texture = data->textures->west; //Depende de donde aunte el rayo
		}
		else //si se ha chocado con una pared horizontal
		{
			if (step_y == -1)
				wall_texture = data->textures->south; //Depende de donde aunte el rayo
			else
				wall_texture = data->textures->north;//Depende de donde aunte el rayo
		}
		tex_x = (int)((double)wall_texture->width * wall_x); //columna actual para printar sus pixeles
		step = (double)wall_texture->height / wall_height; //Calcular si la foto no se ve completa, cuantos pixeles ha de saltar para pasar al siguiente
		tex_pos = (draw_start - WINDOW_HEIGHT / 2 + wall_height / 2) * step; //posisicon principal para empezar a printar la pared, protege de en caso ver toda una pared con zoom empezar del medio
		int	i = 0;
		while (i < draw_start) //pintar suelo
		{
			mlx_put_pixel(data->mlx->img, current_col, i, data->colors->floor);
			i++;
		}
		while (i < draw_end) //pintar pared
		{
			int	pixel = ft_get_pixel(wall_texture, tex_x, (int)tex_pos); //Coger el pixel exacto y pasarlo a uint32_t
			mlx_put_pixel(data->mlx->img, current_col, i, pixel);
			tex_pos += step;
			i++;
		}
		while (i < WINDOW_HEIGHT) //pintar cielo
		{
			mlx_put_pixel(data->mlx->img, current_col, i, data->colors->ceiling);
			i++;
		}
	}
}

#include <stdlib.h>

void	ft_move(mlx_key_data_t key, void *param)
{
	t_data	*data;
	double	speed;
	double	buffer;
	double	move_x;
	double	move_y;
	double	total_move_x;
	double	total_move_y;

	data = (t_data *)param;
	speed = 0.2;
	buffer = 0.2; //change this
	move_x = 0;
	move_y = 0;
	total_move_x = 0;
	total_move_y = 0;
	if (key.key == MLX_KEY_ESCAPE)
		exit(1);
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_A || key.key == MLX_KEY_D || key.key == MLX_KEY_S)
	{
		//Se calcula el total del movimiento
		if (key.key == MLX_KEY_W)
		{
			move_x = data->player->dir_x * speed;
			move_y = data->player->dir_y * speed;
			// if (data->map->map[(int)(data->player->pos_y + data->player->dir_y * (speed + buffer))][(int)data->player->pos_x] != '1')
				// data->player->pos_y += data->player->dir_y * speed;
			// if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + data->player->dir_x * (speed + buffer))] != '1')
				// data->player->pos_x += data->player->dir_x * speed;
		}
		//Se hace -data porque la tecla S va para atras de donde apuntamos
		if (key.key == MLX_KEY_S)
		{
			move_x = -data->player->dir_x * speed;
			move_y = -data->player->dir_y * speed;
			// if (data->map->map[(int)(data->player->pos_y - data->player->dir_y * (speed + buffer))][(int)data->player->pos_x] != '1')
				// data->player->pos_y -= data->player->dir_y * speed;
			// if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x - data->player->dir_x * (speed + buffer))] != '1')
				// data->player->pos_x -= data->player->dir_x * speed;
		}
		//Se usa plan porque es horizontal y el valor es de nuestro hombro a la derecha es +1, por eso A = izquierda(-1) y D normal
		if (key.key == MLX_KEY_A)
		{
			move_x = -data->player->plane_x * speed;
			move_y = -data->player->plane_y *speed;
			// if (data->map->map[(int)(data->player->pos_y - data->player->plane_y * (speed + buffer))][(int)data->player->pos_x] != '1')
				// data->player->pos_y -= data->player->plane_y * speed;
			// if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x - data->player->plane_x * (speed + buffer))] != '1')
				// data->player->pos_x -= data->player->plane_x * speed;
		}
		if (key.key == MLX_KEY_D)
		{
			move_x = data->player->plane_x * speed;
			move_y = data->player->plane_y * speed;
			// if (data->map->map[(int)(data->player->pos_y + data->player->plane_y * (speed + buffer))][(int)data->player->pos_x] != '1')
				// data->player->pos_y += data->player->plane_y * speed;
			// if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + data->player->plane_x * (speed + buffer))] != '1')
				// data->player->pos_x += data->player->plane_x * speed;
		}
		//Porque hay que sumar buffer a la direccion a la que vayamos porque hace de escudo,
		if (move_x > 0)
			total_move_x = move_x + buffer;
		else
			total_move_x = move_x - buffer;
		if (move_y > 0)
			total_move_y = move_y + buffer;
		else
			total_move_y = move_y - buffer;
		if (data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + total_move_x)] != '1' &&
			data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + total_move_x)] != '_' && 
			data->map->map[(int)data->player->pos_y][(int)(data->player->pos_x + total_move_x)] != '|')
			data->player->pos_x += move_x;
		if (data->map->map[(int)(data->player->pos_y + total_move_y)][(int)data->player->pos_x] != '1' &&
			data->map->map[(int)(data->player->pos_y + total_move_y)][(int)data->player->pos_x] != '_' &&
			data->map->map[(int)(data->player->pos_y + total_move_y)][(int)data->player->pos_x] != '|')
			data->player->pos_y += move_y;
	}
	double	old_dir_x;
	double	old_plane_x;
	if (key.key == MLX_KEY_LEFT)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = old_dir_x * cos(-speed) - data->player->dir_y * sin(-speed);
		data->player->dir_y = old_dir_x * sin(-speed) + data->player->dir_y * cos(-speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = old_plane_x * cos(-speed) - data->player->plane_y * sin(-speed);
		data->player->plane_y = old_plane_x * sin(-speed) + data->player->plane_y * cos(-speed);
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		old_dir_x = data->player->dir_x;
		data->player->dir_x = old_dir_x * cos(speed) - data->player->dir_y * sin(speed);
		data->player->dir_y = old_dir_x * sin(speed) + data->player->dir_y * cos(speed);
		old_plane_x = data->player->plane_x;
		data->player->plane_x = old_plane_x * cos(speed) - data->player->plane_y * sin(speed);
		data->player->plane_y = old_plane_x * sin(speed) + data->player->plane_y * cos(speed);
	}

	int		map_x;
	int		map_y;
	
	map_x = (int)data->player->pos_x;
	map_y = (int)data->player->pos_y;
	if (key.key == MLX_KEY_E && key.action == MLX_PRESS)
	{	
		 
		if (map_y + 1 < data->map->height && (data->map->map[map_y + 1][map_x] == '_' || data->map->map[map_y + 1][map_x] == '|'))
			data->map->map[map_y + 1][map_x] = 'O';
		else if (map_y - 1 >= 0 &&  (data->map->map[map_y - 1][map_x] == '_' || data->map->map[map_y - 1][map_x] == '|'))
			data->map->map[map_y - 1][map_x] = 'O';
		else if (map_x + 1 < data->map->width && (data->map->map[map_y][map_x + 1] == '_' || data->map->map[map_y][map_x + 1] == '|'))
			data->map->map[map_y][map_x + 1] = 'O';
		else if (map_x - 1 >= 0 && (data->map->map[map_y][map_x - 1] == '_' || data->map->map[map_y][map_x - 1] == '|'))
			data->map->map[map_y][map_x - 1] = 'O';
		else {
			//if (data->map->map[(int)data->player->pos_y][(int)data->player->pos_x] == 'O')
			//	return ;
			if (map_y + 1 < data->map->height && data->map->map[map_y + 1][map_x] == 'O')
				data->map->map[map_y + 1][map_x] = '_';
			else if (map_y - 1 >= 0 && data->map->map[map_y - 1][map_x] == 'O')
				data->map->map[map_y - 1][map_x] = '_';
			else if (map_x + 1 < data->map->width && data->map->map[map_y][map_x + 1] == 'O')
				data->map->map[map_y][map_x + 1] = '|';
			else if (map_x - 1 >= 0 && data->map->map[map_y][map_x - 1] == 'O')
				data->map->map[map_y][map_x - 1] = '|';
		}
	}
}

# define RED_COLOR 0xFF0000FF
# define WHITE_COLOR 0xFFFFFFFF
# define PURPLE_COLOR 0x333333FF
# define BLACK_COLOR 0x000000FF

void	ft_draw_player(t_data *data)
{
	int	player_side = 8;	
	int init_row = WINDOW_HEIGHT - MINIMAP_HEIGHT + (MINIMAP_HEIGHT / 2 - (player_side / 2));
	int final_row = WINDOW_HEIGHT - MINIMAP_HEIGHT + (MINIMAP_HEIGHT / 2 + (player_side / 2));
	int init_col = MINIMAP_WIDTH / 2 - (player_side / 2);
	int final_col = MINIMAP_WIDTH / 2 + (player_side / 2);
	int current_col;

	while (init_row++ <= final_row)
	{
		current_col = init_col;
		while (current_col++ <= final_col)
			mlx_put_pixel(data->mlx->img, current_col, init_row, RED_COLOR);
	}
}

void ft_minimap(void *param)
{
	t_data	*data = (t_data *)param;
	int pixel_row  = WINDOW_HEIGHT - MINIMAP_HEIGHT;
	int pixel_col;

	double view = 7.0; //constant
	double	pixels_each_field = (double)MINIMAP_HEIGHT / view; //34
	
	double rel_x;
	double rel_y;
	int		map_x;
	int		map_y;
	while (pixel_row < WINDOW_HEIGHT - 1)
	{
		pixel_col = 1;
		while (pixel_col < MINIMAP_WIDTH)
		{
			if (pixel_row == WINDOW_HEIGHT - MINIMAP_HEIGHT || pixel_row == WINDOW_HEIGHT - MINIMAP_HEIGHT + 1 || pixel_row == WINDOW_HEIGHT - 2 || pixel_row == WINDOW_HEIGHT - 3
				|| pixel_col == 1 || pixel_col == 2 || pixel_col == MINIMAP_WIDTH - 1 || pixel_col == MINIMAP_WIDTH - 2)
				mlx_put_pixel(data->mlx->img, pixel_col, pixel_row, RED_COLOR);
			else
			{
				rel_x = (pixel_col - (MINIMAP_WIDTH / 2)) / pixels_each_field;
				rel_y = (pixel_row - (WINDOW_HEIGHT - (MINIMAP_HEIGHT / 2))) / pixels_each_field;
				map_x = (int)floor(data->player->pos_x + rel_x);
				map_y = (int)floor(data->player->pos_y + rel_y);

				if (map_x >= 0 && map_y >= 0 &&  map_x < data->map->width && map_y < data->map->height
						&& data->map->map[map_y] && data->map->map[map_y][map_x] == '1')
					mlx_put_pixel(data->mlx->img, pixel_col, pixel_row, WHITE_COLOR);
				else
					mlx_put_pixel(data->mlx->img, pixel_col, pixel_row, BLACK_COLOR);
			}
			pixel_col++;
		}
		pixel_row++;
	}
	ft_draw_player(data);
}

void	ft_game_loop(t_data *data)
{
	mlx_loop_hook(data->mlx->window, ft_render, data);
	mlx_key_hook(data->mlx->window, ft_move, data);
	mlx_loop_hook(data->mlx->window, ft_minimap, data);
	mlx_loop(data->mlx->window);
}
