/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errorctx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvillavi <mvillavi@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 19:15:12 by mvillavi          #+#    #+#             */
/*   Updated: 2026/01/10 23:33:37 by mvillavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

#include <stdbool.h> //bool return ft
#include "errorctx.h" //struct

typedef enum e_config_type
{
	NO,
	SO,
	WE,
	EA,
	F,
	C,
	CONFIG_COUNT,
}	t_config_type;

typedef enum e_cfg_result
{
    CFG_DONE,
    CFG_OK,
    CFG_ERROR,
}	t_cfg_result;

int		ft_find_config(char *line);
bool	ft_check_all_defined(bool flags[]);
int		ft_handler_founded_errors(int type_found, char *line, bool *flags, t_error *error);
void	ft_remove_map(int last_cfg_line, char **file_content);

#endif