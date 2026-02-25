/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 16:25:22 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"
#include "MLX42.h"
#include "libft.h"

#define BLACK 0x000000FF

static void	ft_black_screen(t_data *data)
{
	int	row;
	int	col;

	row = -1;
	data->textures->weapon->idle->enabled = false;
	data->textures->weapon->shoot->enabled = false;
	data->textures->weapon->smoke->enabled = false;
	while (++row < WINDOW_HEIGHT)
	{
		col = -1;
		while (++col < WINDOW_WIDTH)
			mlx_put_pixel(data->mlx->framebuffer, col, row, BLACK);
	}
}

static void	ft_put_finish_image(int finish_type, t_data *data)
{
	if (finish_type == DIE)
		mlx_image_to_window(data->mlx->window, data->textures->game_over,
			WINDOW_WIDTH / 2 - data->textures->game_over->width / 2,
			WINDOW_HEIGHT / 2 - data->textures->game_over->height / 2);
	else if (finish_type == KILL_ALL_ENEMIES)
		mlx_image_to_window(data->mlx->window, data->textures->victory,
			WINDOW_WIDTH / 2 - data->textures->victory->width / 2,
			WINDOW_HEIGHT / 2 - data->textures->victory->height / 2);
}

static void	ft_final_time_played(t_data *data)
{
	char	*tmp;
	char	*time_str;

	if (data->textures->timer)
		mlx_delete_image(data->mlx->window, data->textures->timer);
	tmp = ft_itoa((int)mlx_get_time());
	time_str = ft_strjoin("Time played: ", tmp);
	data->textures->timer = mlx_put_string(data->mlx->window, time_str,
			WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 200);
	mlx_resize_image(data->textures->timer, 300, 50);
	free(tmp);
	free(time_str);
}

void	ft_handle_endgame(t_data *data)
{
	static bool	not_first;

	if (not_first == false)
	{
		ft_black_screen(data);
		if (data->game_over == DIE && not_first == false)
			ft_put_finish_image(DIE, data);
		else if (data->game_over == KILL_ALL_ENEMIES && not_first == false)
			ft_put_finish_image(KILL_ALL_ENEMIES, data);
		ft_final_time_played(data);
	}
	not_first = true;
}
