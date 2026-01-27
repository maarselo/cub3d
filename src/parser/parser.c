/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:05:38 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h" //struct in parser
#include "cub3d.h" //t_data struct
#include "errorctx.h" //error struct
#include "free.h" //ft_free_data
#include "utils.h" //ft_read_file
#include "libft.h"
#include "parser_internal.h" //add to struct data

void	ft_init_colors(char *file, t_data *data)
{
	char		**content;
	t_colors	*colors;

	colors = (t_colors *)ft_calloc(1, sizeof(t_colors));
	if (!colors)
		return (ft_free_data(data), ft_set_error_system(data->error));
	content = ft_read_file(file, data->error);
	if (!content)
		return (free(colors), ft_free_data(data),
			ft_set_error_system(data->error));
	//..take the colors to hexadecimal and handler
	return ; //to test
}

void	ft_parser(char *file, t_data *data, t_error *error)
{
	if (ft_has_error(error))
		return ;
	data->error = error;
	ft_init_colors(file, data);
	ft_init_textures(file, data);
}
