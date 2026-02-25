/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 16:20:40 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "cub3d.h"
#include "MLX42.h"
#include "errorctx.h"
#include "game_internal.h"

void	ft_put_weapon_images(t_data *data);

void	ft_update_animation(t_data *data);
void	ft_render(t_data *data);
void	ft_draw_enemies(t_data *data);
void	ft_minimap(t_data *data);
void	ft_point(t_data *data);
void	ft_timer(t_data *data);
void	ft_monitor_player_death(t_data *data);

void	ft_move(mlx_key_data_t key, void *param);
void	ft_mouse(double x, double y, void *param);
void	ft_shoot(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);

void	ft_handle_endgame(t_data *data);

static void	ft_register_game_hooks(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_monitor_player_death(data);
	if (ft_end_game(data))
		return (ft_handle_endgame(data));
	ft_render(data);
	ft_update_animation(data);
	ft_draw_enemies(data);
	ft_minimap(data);
	ft_timer(data);
	ft_point(data);
}

void	ft_game_loop(t_data *data)
{
	if (ft_has_error(data->error))
		return ;
	ft_put_weapon_images(data);
	mlx_set_cursor_mode(data->mlx->window, MLX_MOUSE_DISABLED);
	mlx_loop_hook(data->mlx->window, ft_register_game_hooks, data);
	mlx_key_hook(data->mlx->window, ft_move, data);
	mlx_cursor_hook(data->mlx->window, ft_mouse, data);
	mlx_mouse_hook(data->mlx->window, ft_shoot, data);
	mlx_loop(data->mlx->window);
}
