/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include "utils.h" //ft_count_lines and read content
#include "libft.h" //ft_isspace_str
#include "validator/config.h" //struct flags and macros
#include <stdbool.h> //bool array 
#include "free.h" //ft_free_file

static void	ft_check_empty_file(char *file, t_error *error)
{
	int		total_lines;

	total_lines = ft_count_lines(file, error);
	if (ft_has_error(error))
		return ;
	else if (total_lines == 0)
		return (ft_set_error_static(EMPTY_FILE, error, VALIDATOR));
}

static void	ft_validate_config(char **content, t_error *error)
{
	int		idx;
	int		type_found;
	int		result;
	bool	flags[CONFIG_COUNT];

	if (ft_has_error(error) || content == FT_FAILED_PTR)
		return ;
	idx = -1;
	ft_memset(flags, 0, sizeof(flags));
	while (content[++idx])
	{
		if (ft_isspace_str(content[idx]))
			continue ;
		type_found = ft_find_config(content[idx]);
		result = ft_validate_cfg_line(type_found, content[idx], flags, error);
		if (result == CFG_DONE)
			return (ft_remove_map(idx, content));
		else if (result == CFG_ERROR)
			return (ft_free_file_content(content));
		flags[type_found] = true;
	}
	if (!ft_check_all_defined(flags))
		return (ft_free_file_content(content),
			ft_set_error_static(CONFIG_NOT_DEFINED, error, VALIDATOR));
	return (ft_set_error_static(MAP_NOT_DEFINED, error, VALIDATOR));
}
/*
void	ft_validate_has_paths(char **content)
{
}*/

void	ft_check_config(char *file, t_error *error)
{
	char	**content;

	if (ft_has_error(error))
		return ;
	ft_check_empty_file(file, error);
	content = ft_read_file(file, error);
	ft_validate_config(content, error);
	//ft_validate_has_paths(content);
}
