/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 20:55:55 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data struct
#include "errorctx.h" //error struct
#include "parser.h" //struct in parser

mlx_image_t	*ft_texture_to_img(t_data *data, char *texture_str)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(texture_str);
	if (!texture)
		ft_set_error_mlx(data->error);
	image = mlx_texture_to_image(data->mlx->window, texture);
	mlx_delete_texture(texture);
	if (!image)
		ft_set_error_mlx(data->error);
	return (image);
}

void	ft_init_textures(char *file, t_data *data)
{
	char	**content;
	char	**line;
	int		i;
	int		j;

	content = ft_read_file(file, data->error);
	if (!content)
		return (ft_free_data(data), ft_set_error_system(data->error));
	i = -1;
	j = 0;
	while (content[++i])
	{
		if (ft_find_config(content[i]) != -1)
		{
			line = ft_split(content[i], ' ');
			if (ft_strncmp(line[1], "NO", 2))
				data->textures->north = ft_texture_to_img(data, line[1]);
			if (ft_strncmp(line[1], "SO", 2))
				data->textures->south = ft_texture_to_img(data, line[1]);
			if (ft_strncmp(line[1], "WE", 2))
				data->textures->west = ft_texture_to_img(data, line[1]);
			if (ft_strncmp(line[1], "EA", 2))
				data->textures->east = ft_texture_to_img(data, line[1]);
		}
	}
}
