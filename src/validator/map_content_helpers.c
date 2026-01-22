/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbanzo-s <fbanzo-s@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/22 21:29:49 by fbanzo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator/config.h" //enum var
#include "../../libs/libft/include/libft.h" //len and strnstr

int	ft_get_map_start_idx(char **content)
{
	int		i;
	int		j;
	int		cfg_found;

	i = -1;
	cfg_found = 0;
	while (content[++i] && cfg_found < CONFIG_COUNT)
	{
		if (ft_isspace_str(content[i]))
			continue; ;
		j = -1;
		while (g_config_string[++j])
		{
			if (ft_strnstr(content[i], g_config_string[j],
					ft_strlen(content[i])))
			{
				cfg_found++;
				break ;
			}
		}
	}
	while (content[i] && ft_isspace_str(content[i]))
		i++ ;
	return (i);
}

int	ft_get_map_last_idx(int start_idx, char **content)
{
	int	idx;
	int	last_idx;

	idx = start_idx;
	while (content[idx])
	{
		if (ft_isspace_str(content[idx]))
		{
			idx++;
			continue ;
		}
		else
			last_idx = idx;
		idx++;
	}
	return (last_idx);
}

char	*ft_replace_spaces(int chars, char *str, t_error *error)
{
	char	*str1;
	char	*str2;
	int		i;

	str1 = (char *)malloc(sizeof(char) * chars + 1);
	if (!str1)
		return (ft_set_error_system(error), NULL);
	i = -1;
	while (++i < chars)
		str1[i] = '-';
	str1[i] = '\0';
	str2 = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!str2)
		return (ft_set_error_system(error), NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			str2[i] = '-';
		else
			str2[i] = str[i];
	}
	str2[i] = '\0';
	return (free(str), ft_strjoin(str2, str1));
}

int	ft_get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}