/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator/config.h"//enum
#include "errorctx.h" //struct
#include "libft.h" //ft_strlen
#include <stdbool.h> //bool array 

static const char	*config_string[CONFIG_COUNT] = {
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

int	ft_find_config(char *line)
{
	int	idx;
	int	len;

	idx = -1;
	len = ft_strlen(line);
	while (++idx < CONFIG_COUNT)
	{
		if (ft_strnstr(line, config_string[idx], len))
			return (idx);
	}
	return (FT_FAILED_INT);
}

static bool	ft_has_multi_statement(int type, char *line)
{
	int		idx;
	int		len;
	char	*match;

	idx = -1;
	len = ft_strlen(line);
	while (++idx < CONFIG_COUNT)
	{
		if (idx == type)
		{
			match = ft_strnstr(line, config_string[type], len);
			if (ft_strnstr(line + (match - line + ft_strlen(config_string[type])), config_string[type], len))
				return (true);
		}
		else if (ft_strnstr(line, config_string[idx], len))
			return (true);
	}
	return (false);
}


int	ft_handler_founded_errors(int type, char *line, bool *flags, t_error *error)
{
	if (type == FT_FAILED_INT)
	{
		if (ft_check_all_defined(flags))
			return (CFG_DONE);
		return (ft_set_error_static(CONFIG_NOT_DEFINED, error, VALIDATOR), CFG_ERROR);
	}
	else if (ft_has_multi_statement(type, line))
		return (ft_set_error_static(MULTI_STATEMENT, error, VALIDATOR), 1);
	else if (flags[type] == true)
		return (ft_set_error_static(DUP_CFG, error, VALIDATOR), CFG_ERROR);
	return (CFG_OK);
}

void	ft_remove_map(int last_cfg_line, char **file_content)
{
	int	current_line;

	current_line = last_cfg_line;
	if (!file_content[current_line])
		return ;
	while (file_content[current_line])
	{
		free(file_content[current_line]);
		file_content[current_line++] = NULL;
	}
}
