/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/26 17:23:33 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "cub3d.h"
#include "parser.h"
#include "game.h"
#include "game_internal.h"

static mlx_image_t	*ft_check_hit(t_data *data)
{
	while (!data->render->wall.hit)
	{
		if (data->render->side_dist_x < data->render->side_dist_y)
		{
			data->render->side_dist_x += data->render->delta_dist_x;
			data->render->map_x += data->render->step_x;
			data->render->wall.side = 0;
		}
		else
		{
			data->render->side_dist_y += data->render->delta_dist_y;
			data->render->map_y += data->render->step_y;
			data->render->wall.side = 1;
		}
		if (data->map->map[data->render->map_y][data->render->map_x] == '1')
			data->render->wall.hit = true;
		else if (data->map->map[data->render->map_y][data->render->map_x]
			== '_'
			|| data->map->map[data->render->map_y][data->render->map_x]
			== '|')
			return (data->render->wall.hit = true, data->textures->door);
	}
	return (NULL);
}

static void	ft_draw(t_data *data, int curr_col, mlx_image_t *wall_texture)
{
	int	i;

	i = 0;
	while (i < data->render->wall.draw_start)
	{
		mlx_put_pixel(data->mlx->framebuffer, curr_col,
			i, data->colors->floor);
		i++;
	}
	while (i < data->render->wall.draw_end)
	{
		mlx_put_pixel(data->mlx->framebuffer, curr_col, i,
			ft_get_pixel((int)data->render->wall.tex_pos,
				data->render->wall.tex_x, wall_texture));
		data->render->wall.tex_pos += data->render->wall.step;
		i++;
	}
	while (i < WINDOW_HEIGHT)
	{
		mlx_put_pixel(data->mlx->framebuffer,
			curr_col, i, data->colors->ceiling);
		i++;
	}
}

static void	ft_init_dda_data(t_data *data)
{
	if (data->render->ray_dir_x < 0)
	{
		data->render->step_x = -1;
		data->render->side_dist_x = (data->player->pos_x
				- data->render->map_x) * data->render->delta_dist_x;
	}
	else
	{
		data->render->step_x = 1;
		data->render->side_dist_x = (data->render->map_x + 1.0
				- data->player->pos_x) * data->render->delta_dist_x;
	}
	if (data->render->ray_dir_y < 0)
	{
		data->render->step_y = -1;
		data->render->side_dist_y = (data->player->pos_y
				- data->render->map_y) * data->render->delta_dist_y;
	}
	else
	{
		data->render->step_y = 1;
		data->render->side_dist_y = (data->render->map_y + 1.0
				- data->player->pos_y) * data->render->delta_dist_y;
	}
}

static void	ft_calc_wall_dist(t_data *data)
{
	if (data->render->wall.side == 0)
	{
		data->render->wall.perpend_dist = data->render->side_dist_x
			- data->render->delta_dist_x;
		data->render->wall.wall_x = data->player->pos_y
			+ data->render->ray_dir_y * data->render->wall.perpend_dist;
	}
	else
	{
		data->render->wall.perpend_dist = data->render->side_dist_y
			- data->render->delta_dist_y;
		data->render->wall.wall_x = data->player->pos_x
			+ data->render->ray_dir_x * data->render->wall.perpend_dist;
	}
}

void	ft_render(void *param)
{
	int			curr_col;
	mlx_image_t	*wall_texture;
	t_data		*data;

	data = (t_data *)param;
	curr_col = -1;
	while (++curr_col < WINDOW_WIDTH)
	{
		wall_texture = NULL;
		ft_set_render_data(data, curr_col);
		ft_set_delta_dist(data);
		ft_init_dda_data(data);
		data->render->wall.hit = false;
		wall_texture = ft_check_hit(data);
		wall_texture = ft_set_wall_texture(data, wall_texture);
		ft_calc_wall_dist(data);
		data->render->wall.wall_x -= floor(data->render->wall.wall_x);
		data->render->wall.wall_height = (int)(WINDOW_HEIGHT
				/ data->render->wall.perpend_dist);
		ft_set_draw_pos(data);
		ft_set_tex_params(data, wall_texture);
		ft_draw(data, curr_col, wall_texture);
		data->mlx->z_buffer[curr_col] = data->render->wall.perpend_dist;
	}
}
