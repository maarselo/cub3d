/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:47 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errorctx.h" //struct
#include <errno.h> //errno in open file
#include <fcntl.h> //open()
#include "libft.h" //gnl, and ft_substr
#include "utils/utils_internal.h"

int	ft_open_file(char *file, t_error *error)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_set_error_join(errno, file, error, SYSTEM), FT_FAILED_INT);
	return (fd);
}

int	ft_count_lines(char *file, t_error *error)
{
	int		fd;
	int		total_lines;
	char	*line;

	total_lines = 0;
	fd = ft_open_file(file, error);
	if (ft_has_error(error))
		return (FT_FAILED_INT);
	line = get_next_line(fd);
	while (line)
	{
		total_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (total_lines);
}

char	**ft_read_file(char *file, t_error *error)
{
	int		i;
	int		fd;
	int		total_lines;
	char	**file_content;

	total_lines = ft_count_lines(file, error);
	if (ft_has_error(error))
		return (FT_FAILED_PTR);
	fd = ft_open_file(file, error);
	if (ft_has_error(error))
		return (FT_FAILED_PTR);
	file_content = (char **)ft_calloc(total_lines + 1, sizeof(char *));
	if (!file_content)
		return (ft_set_error_system(error), FT_FAILED_PTR);
	i = -1;
	while (++i < total_lines)
	{
		file_content[i] = ft_get_clean_line(&fd);
		if (!file_content[i])
			ft_free_content_assigned(i, file_content);
	}
	file_content[total_lines] = NULL;
	close(fd);
	return (file_content);
}
