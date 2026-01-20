/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdbool.h" //returns and array
#include "validator/config.h" //enum values
#include "libft.h" //ft_strlen and ft_strnstr
#include "errorctx.h" //fucntons
#include "validator/config_validator.h" //auxiliar functions
#include "free.h"

const char	*g_config_string[CONFIG_COUNT] = {
[NO] = "NO ",
[SO] = "SO ",
[WE] = "WE ",
[EA] = "EA ",
[F] = "F ",
[C] = "C "
};

bool	ft_check_all_defined(bool flags[])
{
	int	idx;

	idx = -1;
	while (++idx < CONFIG_COUNT)
	{
		if (!flags[idx])
			return (false);
	}
	return (true);
}

int	ft_validate_cfg_line(int type, char *line, bool *flags, t_error *error)
{
	if (type == FT_FAILED_INT)
	{
		if (error->error_number == INVALID_ORDER)
			return (CFG_ERROR);
		if (ft_check_all_defined(flags))
			return (CFG_DONE);
		return (ft_set_error_static(CONFIG_NOT_DEFINED, error, VALIDATOR),
			CFG_ERROR);
	}
	else if (ft_has_multi_statement(type, line))
		return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR), 1);
	else if (flags[type] == true)
		return (ft_set_error_static(DUP_CFG, error, VALIDATOR), CFG_ERROR);
	return (CFG_OK);
}

int	ft_has_path(char *cfg_line, t_error *error)
{
	int		i;
	char	**split_line;

	i = 0;
	split_line = ft_split(cfg_line, ' ');
	if (!split_line)
		return (ft_set_error_system(error), 0);
	while (split_line[i])
		i++;
	if (i < 2)
		return (ft_set_error_static(CFG_TEX_WITHOUT_PATH, error, VALIDATOR), 0);
	else if (i > 2)
		return (ft_set_error_static(CFG_TEX_MULTI_PATHS, error, VALIDATOR), 0);
	return (1);
}

static void	ft_strtrim_spaces(char **split)
{
	int		idx;
	char	*tmp;

	idx = -1;
	while (split[++idx])
	{
		tmp = split[idx];
		split[idx] = ft_strtrim(split[idx], " ");
		free(tmp);
	}
}

int	ft_has_correct_colors(char *cfg_line, t_error *error)
{
	int		i;
	char	*value;
	char	**split_line;

	i = 0;
	while (ft_isspace(cfg_line[i]))
		i++;
	value = cfg_line + i + 1;
	if (ft_isspace_str(value))
		return (ft_set_error_static(CFG_COLOR_UNDEF, error, VALIDATOR), 0);
	if (ft_get_lastc(value) == ',')
		return (ft_set_error_static(CFG_COLOR_LASTC_COMMA, error, VALIDATOR), 0);
	if (ft_has_consecutive_commas(value))
		return (ft_set_error_static(CFG_COLOR_CONSECUTIVE_COMMAS, error, VALIDATOR), 0);
	split_line = ft_split(value, ',');
	if (!split_line)
		return (ft_set_error_system(error), 0);
	if (!ft_has_valid_value_count(split_line))
		return (ft_free_split(split_line), ft_set_error_static(CFG_COLOR_INVALID_VALUE_COUNT, error, VALIDATOR), 0);
	ft_strtrim_spaces(split_line);
	if (ft_has_invalid_characters(split_line))
		return (ft_free_split(split_line), ft_set_error_static(CFG_COLOR_INVALID_CHARS, error, VALIDATOR), 0);
	if (!ft_has_correct_color_range(split_line))
		return (ft_free_split(split_line), ft_set_error_static(CFG_COLOR_INVALID_RANGE, error, VALIDATOR), 0);
	return (1);
}
