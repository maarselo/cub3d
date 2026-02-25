/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 12:57:25 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "errorctx.h"
#include "game.h"
#include "game_internal.h"
#include <math.h>

void ft_minimap(void *param);
void ft_render(void *param);
void ft_move(mlx_key_data_t key, void *param);

#include <stdlib.h>
#include <sys/time.h>

# define RED_COLOR 0xFF0000FF
# define WHITE_COLOR 0xFFFFFFFF
# define PURPLE_COLOR 0x333333FF
# define BLACK_COLOR 0x000000FF

#define MIDDLE_WIDTH WINDOW_WIDTH / 2

void	ft_put_weapon_images(t_data *data)
{
	int	row;

	row = WINDOW_HEIGHT - data->textures->weapon->idle->height;
	mlx_image_to_window(data->mlx->window, data->textures->weapon->idle, MIDDLE_WIDTH, row);
	row = WINDOW_HEIGHT - data->textures->weapon->shoot->height;
	mlx_image_to_window(data->mlx->window, data->textures->weapon->shoot, MIDDLE_WIDTH, row);
	data->textures->weapon->shoot->enabled = false;
	row = WINDOW_HEIGHT - data->textures->weapon->smoke->height;
	mlx_image_to_window(data->mlx->window, data->textures->weapon->smoke, MIDDLE_WIDTH, row);
	data->textures->weapon->smoke->enabled = false;
}

#include "libft.h"

void	ft_timer(void *param)
{
	t_data	*data;
	char	*tmp;
	char	*timer_str;
	data = (t_data *)param;

	if (data->textures->timer)
		mlx_delete_image(data->mlx->window, data->textures->timer);
	tmp = ft_itoa((int)mlx_get_time());
	timer_str = ft_strjoin("Time played: ", tmp);
	free(tmp);
	data->textures->timer = mlx_put_string(data->mlx->window, timer_str, 0,0);
	free(timer_str);
}

void	ft_date(void *param)
{
	static long	last_min_update = -1;
	struct timeval	time_struct;
	long	today_seconds;
	long	actual_hours_nb;
	long	actual_minutes_nb;
	char	*tmp;
	char	*actual_hours;
	char	*actual_minutes;
	char	*date;
	t_data	*data;

	gettimeofday(&time_struct, NULL);
	if (last_min_update == time_struct.tv_sec / 60)
		return ;
	last_min_update = time_struct.tv_sec / 60;
	data = (t_data *)param;
	today_seconds = (time_struct.tv_sec + 3600) % 86400; //suma de 3600 para que de la hora espanoa invierno
	actual_hours_nb = today_seconds / 3600;
	if (data->textures->date)
		mlx_delete_image(data->mlx->window, data->textures->date);
	if (actual_hours_nb < 10)
	{
		tmp = ft_itoa(actual_hours_nb);
		actual_hours = ft_strjoin("0",tmp);
		free(tmp);
	}
	else
		actual_hours = ft_itoa(actual_hours_nb);
	actual_minutes_nb = (today_seconds / 60) % 60;
	if (actual_minutes_nb < 10)
	{
		tmp = ft_itoa(actual_minutes_nb);
		actual_minutes = ft_strjoin("0", tmp);
		free(tmp);
	}
	else
		actual_minutes = ft_itoa(actual_minutes_nb);
	date = ft_multijoin(3, actual_hours, ":", actual_minutes);
	data->textures->date = mlx_put_string(data->mlx->window, date, MIDDLE_WIDTH - 25, 1);
	free(actual_hours);
	free(actual_minutes);
	free(date);
}

void	ft_mouse(double x, double y, void *param)
{
	t_data			*data;
	double			angle;
	double			delta_x;
	double			old_plane_x;
	double			old_dir_x;
	static double	old_x;

	(void)y;
	data = (t_data *)param;
	if (old_x == 0)
	{
		old_x = x;
		return ;
	}
	delta_x = x - old_x;
	angle = delta_x * 0.002;
	old_dir_x = data->player->dir_x;
	data->player->dir_x = old_dir_x * cos(angle) - data->player->dir_y * sin(angle);
	data->player->dir_y = old_dir_x * sin(angle) + data->player->dir_y * cos(angle);
	old_plane_x = data->player->plane_x;
	data->player->plane_x = old_plane_x * cos(angle) - data->player->plane_y * sin(angle);
	data->player->plane_y = old_plane_x * sin(angle) + data->player->plane_y * cos(angle);
	old_x = x;
}

void	ft_point(void *param)
{
	int		i;
	int		j;
	t_data	*data;

	data = (t_data *)param;
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

#define COLLISION 0.1

bool	ft_check_impact_enemy(double row, double col, t_data *data)
{
	double	result_x;
	double	result_y;
	t_enemy	*current_enemy;

	current_enemy = data->enemies->enemies;
	while (current_enemy)
	{
		result_x = fabs(col - current_enemy->pos_x);
		result_y = fabs(row - current_enemy->pos_y);
		if (result_x <= COLLISION && result_y <= COLLISION)
		{
			current_enemy->is_died = true;
			data->map->map[(int)current_enemy->pos_y][(int)current_enemy->pos_x] = '0';
			--data->enemies->total_enemies;
			return (true);
		}
		current_enemy = current_enemy->next;
	}
	return (false);
}

void ft_shoot(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_data		*data;
	double		bullet_x;
	double		bullet_y;
	double		distance;

	(void)mods;
	data =(t_data *)param;
	distance = 0.0;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS && !data->textures->weapon->is_shooting)
	{
		data->textures->weapon->is_shooting = true;
		while (distance <= 2.5)
		{
			bullet_x = data->player->pos_x + data->player->dir_x * distance;
			bullet_y = data->player->pos_y + data->player->dir_y * distance;
			if ((int)bullet_x < 0 || (int)bullet_x >= data->map->width
				|| (int)bullet_y < 0 || (int)bullet_y >= data->map->height)
				break;
			if (data->map->map[(int)bullet_y][(int)bullet_x] != 'e' && data->map->map[(int)bullet_y][(int)bullet_x] != '0')
				break;
			if (ft_check_impact_enemy(bullet_y, bullet_x, data))
				return ;
			distance += 0.1;
		}
	}
}

#define IDLE 0
#define SHOOT 1
#define SMOKE 2

void	ft_change_frame(void *param)
{
	t_data		*data;
	static int	counter;
	static int	frame;

	data = (t_data *)param;
	if (!data->textures->weapon->is_shooting)
	{
		frame = SHOOT;
		return ;
	}
	counter++;	
	if (counter >= 4)
	{
		if (frame == SHOOT)
		{
			data->textures->weapon->idle->enabled = false;
			data->textures->weapon->shoot->enabled = true;
			frame++;
		}
		else if (frame == SMOKE)
		{
			data->textures->weapon->shoot->enabled = false;
			data->textures->weapon->smoke->enabled = true;
			frame = 0;
		}
		else if (frame == IDLE)
		{
			data->textures->weapon->is_shooting = false;
			data->textures->weapon->smoke->enabled = false;
			data->textures->weapon->idle->enabled = true;
			frame++;
		}
		counter = 0;
	}
}

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
					color = ft_get_pixel(frame, tex_x, tex_y);
					if ((color & 0x000000FF) != 0)
						mlx_put_pixel(data->mlx->framebuffer, x, y, color);
				}
			}
		}
		curr = curr->next;
	}
}

#define COLLISION_DIE 0.3

void	ft_check_position(void *param)
{
	double	result_y;
	double	result_x;
	t_data	*data;
	t_enemy	*current_enemy;
	
	data = (t_data *)param;
	if (data->enemies->total_enemies == 0)
		return ;
	current_enemy = data->enemies->enemies;
	while (current_enemy)
	{
		if (current_enemy->is_died)
		{
			current_enemy = current_enemy->next;
			continue ;
		}
		result_x = fabs(data->player->pos_x - current_enemy->pos_x);
		result_y = fabs(data->player->pos_y - current_enemy->pos_y);
		if (result_x <= COLLISION_DIE && result_y < COLLISION_DIE)
		{
			//flag u sistema de termnate 
			mlx_close_window(data->mlx->window);
		}
		current_enemy = current_enemy->next;
	}
}

void	ft_game_loop(t_data *data)
{
	if (ft_has_error(data->error))
		return ;
	ft_put_weapon_images(data);
	mlx_set_cursor_mode(data->mlx->window, MLX_MOUSE_DISABLED);
	mlx_loop_hook(data->mlx->window, ft_date, data);
	mlx_loop_hook(data->mlx->window, ft_timer, data);
	mlx_loop_hook(data->mlx->window, ft_render, data);
	mlx_loop_hook(data->mlx->window, ft_draw_enemies, data);
	mlx_key_hook(data->mlx->window, ft_move, data);
	mlx_loop_hook(data->mlx->window, ft_point, data);
	mlx_loop_hook(data->mlx->window, ft_minimap, data);
	mlx_cursor_hook(data->mlx->window, ft_mouse, data);
	mlx_mouse_hook(data->mlx->window, ft_shoot, data);
	mlx_loop_hook(data->mlx->window, ft_change_frame, data);
	mlx_loop_hook(data->mlx->window, ft_check_position, data);
	mlx_loop(data->mlx->window);
}
