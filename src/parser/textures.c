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
#include "utils.h" //ft_read_fle
#include "libft.h" // ft_fstr*
#include "validator/config/config.h" //detect cfg
#include "free.h" //ft_free_split
 
#define NORTH "NO"
#define SOUTH "SO"
#define WEST "WE"
#define EAST "EA"

#define PATH_CLOSE_DOOR "./textures/door/close.png"
#define PATH_OPEN_DOOR "./textures/door/open.png"

#define PATH_WEAPON_IDLE "./textures/weapon/idle.png"
#define PATH_WEAPON_RELOAD "./textures/weapon/reload.png"
#define PATH_WEAPON_AIM "./textures/weapon/aim.png"
#define PATH_WEAPON_SHOOT "./textures/weapon/shoot.png"

static mlx_image_t	*ft_texture_to_img(char *texture_path, t_data *data)
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

static void	ft_init_orientation_texture(char **cfg_line, t_data *data)
{
	if (!ft_strncmp(cfg_line[0], NORTH, 2))
		data->textures->north = ft_texture_to_img(cfg_line[1], data);
	else if (!ft_strncmp(cfg_line[0], SOUTH, 2))
		data->textures->south = ft_texture_to_img(cfg_line[1], data);
	else if (!ft_strncmp(cfg_line[0], WEST, 2))
		data->textures->west = ft_texture_to_img(cfg_line[1], data);
	else if (!ft_strncmp(cfg_line[0], EAST, 2))
		data->textures->east = ft_texture_to_img(cfg_line[1], data);
	ft_free_split(cfg_line);
}

static void	ft_init_doors_textures(t_data *data)
{
	if (ft_has_error(data->error))
		return ;
	data->textures->door->close = ft_texture_to_img(PATH_CLOSE_DOOR, data);
	data->textures->door->open = ft_texture_to_img(PATH_OPEN_DOOR, data);
}

static void	ft_init_weapons_textures(t_data *data)
{
	if (ft_has_error(data->error))
		return ;
	data->textures->weapon->idle = ft_texture_to_img(PATH_WEAPON_IDLE, data);
	data->textures->weapon->reload = ft_texture_to_img(PATH_WEAPON_RELOAD, data);
	data->textures->weapon->aim = ft_texture_to_img(PATH_WEAPON_AIM, data);
	data->textures->weapon->shoot = ft_texture_to_img(PATH_WEAPON_SHOOT, data);
}

void	ft_init_textures(char *file, t_data *data)
{
	int		i;
	char	**content;
	char	**cfg_line;

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
			cfg_line = ft_split(content[i], ' ');
			if (!cfg_line)
				return (ft_free_file_content(content), ft_set_error_system(data->error));
			ft_init_orientation_texture(cfg_line, data);
		}
	}
	ft_init_doors_textures(data);
	ft_init_weapons_textures(data);
	return (ft_free_file_content(content));
}
