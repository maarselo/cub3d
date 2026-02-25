/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 13:11:21 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "libft.h"

void	ft_timer(void *param)
{
	char	*tmp;
	char	*timer_str;
	t_data	*data;

	data = (t_data *)param;
	if (data->textures->timer)
		mlx_delete_image(data->mlx->window, data->textures->timer);
	tmp = ft_itoa((int)mlx_get_time());
	timer_str = ft_strjoin("Time played: ", tmp);
	free(tmp);
	data->textures->timer = mlx_put_string(data->mlx->window, timer_str, 0, 0);
	free(timer_str);
}
