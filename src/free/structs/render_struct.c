/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 21:18:49 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data
#include "parser.h"//t_map
#include <stdlib.h> //free()

void	ft_free_render(t_data *data)
{
	if (data->render->wall)
		free(data->render->wall);
	free(data->render);
}
