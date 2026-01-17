/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validator.h                                 :+:      :+:    :+:   */
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

static bool	ft_has_multi_statement(int type, char *line)
{
	int		idx;
	int		len;
	int		token_len;
	char	*match;

	idx = -1;
	len = ft_strlen(line);
	while (++idx < CONFIG_COUNT)
	{
		if (idx == type)
		{
			match = ft_strnstr(line, g_config_string[type], len);
			token_len = ft_strlen(g_config_string[type]);
			if (ft_strnstr(match + token_len, g_config_string[type], len))
				return (true);
		}
		else if (ft_strnstr(line, g_config_string[idx], len))
			return (true);
	}
	return (false);
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
		return (ft_set_error_static(CFG_WITHOUT_PATH, error, VALIDATOR), 0);
	else if (i > 2)
		return (ft_set_error_static(CFG_MULTI_PATHS, error, VALIDATOR), 0);
	return (1);
}
#include <stdio.h>
int	ft_has_correct_colors(char *cfg_line, t_error *error)
{
	int		i;
	char	*real_line;
	char	**split_line;

	i = 0;
	while (ft_isspace(cfg_line[i]))
		i++;
	real_line = cfg_line + i + 1;
	/*real_line = ft_strdup_ignore(' ', real_line);
	if (!real_line)
		return (ft_set_error_system(error), 0);
	if (!ft_strlen(real_line))
		return (ft_set_error_static(CFG_COLOR_UNDEF, error, VALIDATOR) , 0);
	*/split_line = ft_split(real_line, ',');
	if (!split_line)
		return (printf("diarrea"),ft_set_error_system(error), 0);
	if (!split_line[0])
		return (printf("caca"));
	if (split_line[0])
		return (printf("%s.", split_line[0]));
	//int j =-1;
	/*while (split_line[++j])
	{
		split_line
	}*/
	return (1);
}
