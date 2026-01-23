/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_validator_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator/config/config.h" //enum_values
#include <stdbool.h> //return
#include "libft.h" //strtrim

bool	ft_has_multi_statement(int type, char *line)
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

bool	ft_has_consecutive_commas(char *line)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		if (line[idx] == ',' && line[idx + 1] && line[idx + 1] == ',')
			return (true);
		idx++;
	}
	return (false);
}

bool	ft_has_valid_value_count(char **split)
{
	int	idx;
	int	count;

	idx = -1;
	count = 0;
	while (split[++idx])
		count++;
	if (count != 3)
		return (false);
	return (true);
}

bool	ft_has_invalid_characters(char **split)
{
	int	i;
	int	j;

	i = -1;
	while (split[++i])
	{
		j = -1;
		if (ft_strchr(split[i], ' '))
			return (true);
		while (split[i][++j])
		{
			if (ft_isalpha(split[i][j]))
				return (true);
		}
	}
	return (false);
}

bool	ft_has_correct_color_range(char **split)
{
	int	idx;
	int	nb;

	idx = -1;
	while (split[++idx])
	{
		nb = ft_atoi(split[idx]);
		if (nb < 0 || nb > 255)
			return (false);
	}
	return (true);
}
