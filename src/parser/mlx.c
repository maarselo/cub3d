/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c	                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:05:38 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data struct
#include "parser.h" //struct in parser
#include "errorctx.h" //ft+_set_error_mlx
#include "game.h" //WINDOW_HEIGHT  and other macros

#define PATH_ICON "./textures/icon/icon.png" 

static void	ft_set_icon(t_data *data)
{
	mlx_texture_t	*icon;

	if (ft_has_error(data->error))
		return ;
	icon = mlx_load_png(PATH_ICON);
	if (!icon)
		return (ft_set_error_mlx(data->error));
	mlx_set_icon(data->mlx->window, icon);
}
/*
static void	ft_set_window_size(t_data *data)
{
	int	monitor_height;
	int	monitor_witdh;

	if (ft_has_error(data->error))
		return ;	
	mlx_get_monitor_size(0, data->mlx->width, data->mlx->height);
}*/

void	ft_init_mlx(t_data *data)
{
	if (ft_has_error(data->error))
		return ;
	data->mlx->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, true);
	if (!data->mlx->window)
		return (ft_set_error_mlx(data->error));
	ft_set_icon(data);
	data->mlx->framebuffer = mlx_new_image(data->mlx->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->mlx->framebuffer)
		return (ft_set_error_mlx(data->error));
	mlx_image_to_window(data->mlx->window, data->mlx->framebuffer, 0, 0);
}
