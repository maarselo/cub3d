/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "utils.h" //ft_count_lines
#include "libft.h" //ft_isspace_str
#include "validator/validator_internal.h" //struct falgs and macros
#include <errno.h>

static void	ft_check_empty_file(char *file, t_error *error)
{
	int		total_lines;

	total_lines = ft_count_lines(file, error);
	if (ft_has_error(error))
		return ;
	else if (total_lines == 0)
		return (ft_set_error_static(EMPTY_FILE, error, VALIDATOR));
}

void	ft_validate_config(char **content, t_error *error)
{
	int				idx;
	int				len;
	t_config_flags	flags;

	if (ft_has_error(error))
		return ;
	idx = -1;
	flags.so_found = false;
	flags.we_found = false;
	flags.ea_found = false;
	flags.f_found = false;
	flags.c_found = false;
	while (content[++idx])
	{
		if (ft_isspace_str(content[idx]))
			continue ;
		len = ft_strlen(content[idx]);
		if (ft_strnstr(content[idx], NORTH_TEX, len))
		{
			if (ft_strnstr(content[idx] + (ft_strnstr(content[idx], NORTH_TEX, len) - content[idx] + ft_strlen(NORTH_TEX)) , NORTH_TEX, len)
				|| ft_strnstr(content[idx], SOUTH_TEX, len)
				|| ft_strnstr(content[idx], WEST_TEX, len)
				|| ft_strnstr(content[idx], EAST_TEX, len)
				|| ft_strnstr(content[idx], FLOOR_COLOR, len)
				|| ft_strnstr(content[idx], CEILING_COLOR, len))
				return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR));
			if (!flags.no_found)
				flags.no_found = true;
			else if (flags.no_found)
				return  (ft_set_error_static(DUPLICATE_NO, error, VALIDATOR));
		}
		else if (ft_strnstr(content[idx], SOUTH_TEX, len))
		{
			if (ft_strnstr(content[idx] + (ft_strnstr(content[idx], SOUTH_TEX, len) - content[idx] + ft_strlen(SOUTH_TEX)), SOUTH_TEX, len)
				|| ft_strnstr(content[idx], NORTH_TEX, len)
				|| ft_strnstr(content[idx], WEST_TEX, len)
				|| ft_strnstr(content[idx], EAST_TEX, len)
				|| ft_strnstr(content[idx], FLOOR_COLOR, len)
				|| ft_strnstr(content[idx], CEILING_COLOR, len))
				return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR));
			if (!flags.so_found)
				flags.so_found = true;
			else if (flags.so_found)
				return  (ft_set_error_static(DUPLICATE_SO, error, VALIDATOR));
		}
		else if (ft_strnstr(content[idx], WEST_TEX, len))
		{
			if (ft_strnstr(content[idx] + (ft_strnstr(content[idx], WEST_TEX, len) - content[idx] + ft_strlen(WEST_TEX)), WEST_TEX, len)
				|| ft_strnstr(content[idx], NORTH_TEX, len)
				|| ft_strnstr(content[idx], SOUTH_TEX, len)
				|| ft_strnstr(content[idx], EAST_TEX, len)
				|| ft_strnstr(content[idx], FLOOR_COLOR, len)
				|| ft_strnstr(content[idx], CEILING_COLOR, len))
				return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR));
			if (!flags.we_found)
				flags.we_found = true;
			else if (flags.we_found)
				return  (ft_set_error_static(DUPLICATE_WE, error, VALIDATOR));
		}
		else if (ft_strnstr(content[idx], EAST_TEX, len))
		{
			if (ft_strnstr(content[idx] + (ft_strnstr(content[idx], EAST_TEX, len) - content[idx] + ft_strlen(EAST_TEX)), EAST_TEX, len)
				|| ft_strnstr(content[idx], NORTH_TEX, len)
				|| ft_strnstr(content[idx], SOUTH_TEX, len)
				|| ft_strnstr(content[idx], WEST_TEX, len)
				|| ft_strnstr(content[idx], FLOOR_COLOR, len)
				|| ft_strnstr(content[idx], CEILING_COLOR, len))
				return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR));
			if (!flags.ea_found)
				flags.ea_found = true;
			else if (flags.ea_found)
				return  (ft_set_error_static(DUPLICATE_EA, error, VALIDATOR));
		}
		else if (ft_strnstr(content[idx], FLOOR_COLOR, len))
		{
			if (ft_strnstr(content[idx] + (ft_strnstr(content[idx], FLOOR_COLOR, len) - content[idx] + ft_strlen(FLOOR_COLOR)), FLOOR_COLOR, len)
				|| ft_strnstr(content[idx], NORTH_TEX, len)
				|| ft_strnstr(content[idx], SOUTH_TEX, len)
				|| ft_strnstr(content[idx], WEST_TEX, len)
				|| ft_strnstr(content[idx], EAST_TEX, len)
				|| ft_strnstr(content[idx], CEILING_COLOR, len))
				return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR));
			if (!flags.f_found)
				flags.f_found = true;
			else if (flags.f_found)
				return  (ft_set_error_static(DUPLICATE_F, error, VALIDATOR));
		}
		else if (ft_strnstr(content[idx], CEILING_COLOR, len))
		{
			if (ft_strnstr(content[idx] + (ft_strnstr(content[idx], CEILING_COLOR, len) - content[idx] + ft_strlen(CEILING_COLOR)), CEILING_COLOR, len)
				|| ft_strnstr(content[idx], NORTH_TEX, len)
				|| ft_strnstr(content[idx], SOUTH_TEX, len)
				|| ft_strnstr(content[idx], WEST_TEX, len)
				|| ft_strnstr(content[idx], EAST_TEX, len)
				|| ft_strnstr(content[idx], FLOOR_COLOR, len))
				return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR));
			if (!flags.c_found)
				flags.c_found = true;
			else if (flags.c_found)
				return  (ft_set_error_static(DUPLICATE_C, error, VALIDATOR));
		}
		else if (flags.no_found && flags.so_found && flags.we_found
			&& flags.ea_found && flags.f_found && flags.c_found)
			return ;
		else
			return (ft_set_error_static(CONFIG_NOT_DEFINED, error, VALIDATOR));
	}
	if (!flags.no_found || !flags.so_found || !flags.we_found
				|| !flags.ea_found || !flags.f_found || !flags.c_found)
				return (ft_set_error_static(CONFIG_NOT_DEFINED, error, VALIDATOR));
}

void	ft_check_map(char *file, t_error *error)
{
	char	**file_content;

	if (ft_has_error(error))
		return ;
	ft_check_empty_file(file, error);
	file_content = ft_read_file(file, error);
	if (ft_has_error(error))
		return ;
	ft_validate_config(file_content, error);
}
