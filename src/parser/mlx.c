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

void	ft_init_mlx(t_data *data)
{
	data->mlx->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", true);
	if (!data->mlx->window)
		return (ft_set_error_mlx(data->error));
}
