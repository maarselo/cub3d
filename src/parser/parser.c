/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/02/24 16:42:58 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h" //struct in parser
#include "cub3d.h" //t_data struct
#include "errorctx.h" //error struct
#include "parser_internal.h" //add to struct data

void	ft_parser(char *file, t_data *data, t_error *error)
{
	if (ft_has_error(error))
		return ;
	data->error = error;
	ft_init_colors(file, data);
	ft_init_map(file, data);
	ft_init_player(data);
	ft_init_minimap(data);
	ft_init_mlx(data);
	ft_init_enemies(data);
	ft_init_textures(file, data);
}
