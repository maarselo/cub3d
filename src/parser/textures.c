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
#include "utils.h" //ft__read_fle
#include "libft.h" // ft_fstr*
#include "validator/config/config.h" //detect cfg
#include "free.h" //ft_free_split
 
static mlx_image_t	*ft_texture_to_img(t_data *data, char *texture_path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(texture_path);
	if (!texture)
		return (ft_set_error_mlx(data->error), NULL);
	image = mlx_texture_to_image(data->mlx->window, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (ft_set_error_mlx(data->error), NULL);
	return (image);
}

void	ft_init_textures(char *file, t_data *data)
{
	int		i;
	char	**content;
	char	**line;

	if (ft_has_error(data->error))
		return ;
	content = ft_read_file(file, data->error);
	if (!content)
		return (ft_set_error_system(data->error));
	i = -1;
	while (content[++i])
	{
		if (ft_find_config(content[i], data->error) != -1)
		{
			line = ft_split(content[i], ' ');
			if (!line)
				return (ft_free_file_content(content), ft_set_error_system(data->error));
			if (!ft_strncmp(line[0], "NO", 2))
				data->textures->north = ft_texture_to_img(data, line[1]);
			else if (!ft_strncmp(line[0], "SO", 2))
				data->textures->south = ft_texture_to_img(data, line[1]);
			else if (!ft_strncmp(line[0], "WE", 2))
				data->textures->west = ft_texture_to_img(data, line[1]);
			else if (!ft_strncmp(line[0], "EA", 2))
				data->textures->east = ft_texture_to_img(data, line[1]);
			ft_free_split(line);
		}
	}
	data->textures->door = ft_texture_to_img(data, "./textures/door.png");
	return (ft_free_file_content(content));
}
