/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/27 21:05:38 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h" //t_data struct
#include "parser.h" //struct in parser
#include "utils.h" //ft_read_file
#include "validator/config/config.h" //utils to detect type
#include "validator/config/config_validator.h" //utils to detect type
#include "libft.h" //ft_utils
#include "free.h" //ft_free_conetn

static	bool	ft_is_cfgcolor(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_strncmp(line + i, g_config_string[C], 2) == 0
			|| ft_strncmp(line + i, g_config_string[F], 2) == 0)
			return (true);
	}
	return (false);
}

static uint32_t	ft_get_rgba(char **split_number)
{
	return (ft_atoi(split_number[0]) << 24 | ft_atoi(split_number[1]) << 16 | ft_atoi(split_number[2]) << 8 | 255);
}

static uint32_t	ft_get_color(char *str, t_data *data)
{
	char		**split_numbers;
	uint32_t	color;

	while (*str && !ft_isdigit(*str))
		str++;
	split_numbers = ft_split(str, ',');
	if (!split_numbers)
		return (ft_set_error_system(data->error), -1);
	ft_strtrim_spaces(split_numbers);
	color = ft_get_rgba(split_numbers);
	return(ft_free_split(split_numbers), color);
}

void	ft_init_colors(char *file, t_data *data)
{
	int			i;
	char		**content;

	if (ft_has_error(data->error))
		return ;
	content = ft_read_file(file, data->error);
	i = -1;
	while (content[++i])
	{
		if (ft_is_cfgcolor(content[i]))
		{
			if (ft_strchr(content[i], 'C'))
				data->colors->ceiling = ft_get_color(content[i], data);
			else if (ft_strchr(content[i], 'F'))
				data->colors->floor = ft_get_color(content[i], data);
			if (ft_has_error(data->error))
				return (ft_free_file_content(content));
		}
	}
	ft_free_file_content(content);
}
