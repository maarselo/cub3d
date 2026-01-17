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
#include "libft.h" //ft_strnstr

int	ft_find_config(char *line, t_error *error)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	len = ft_strlen(line);
	while (++i < CONFIG_COUNT)
	{
		if (ft_strnstr(line, g_config_string[i], len))
		{
			while (ft_isspace(line[j]))
				j++;
			if (ft_strncmp(line + j, g_config_string[i], ft_strlen(g_config_string[i])))
				return (ft_set_error_static(INVALID_ORDER, error, VALIDATOR),
					FT_FAILED_INT);
			return (i);
		}
	}
	return (FT_FAILED_INT);
}

int	ft_detect_cfg_type(int cfg)
{
	if (cfg == NO || cfg == SO || cfg == WE || cfg == EA)
		return (CFG_TEXTURE);
	else
		return (CFG_COLOR);
}

