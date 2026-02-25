/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:14:28 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/25 13:57:30 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "cub3d.h"
#include "parser.h"
#include "libft.h"

void	ft_timer(void *param)
{
	int			seconds;
	char		*str[2];
	t_data		*data;
	static int	old_time;
	static bool	not_first_time;

	data = (t_data *)param;
	seconds = (int)mlx_get_time();
	if (not_first_time == false)
		not_first_time = true;
	else if (old_time ==  seconds)
		return ;
	if (data->textures->timer)
		mlx_delete_image(data->mlx->window, data->textures->timer);
 	str[0] = ft_itoa(seconds);
	str[1] = ft_strjoin("Time played: ", str[0]);
	data->textures->timer = mlx_put_string(data->mlx->window, str[1], 0, 0);
	free(str[0]);
	free(str[1]);
	old_time = seconds;
}
