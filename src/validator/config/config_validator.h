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

#ifndef CONFIG_VALIDATOR_H
# define CONFIG_VALIDATOR_H

//config_validator_helpers.h
bool	ft_has_multi_statement(int type, char *line);
bool	ft_has_consecutive_commas(char *line);
bool	ft_has_valid_value_count(char **split);
bool	ft_has_invalid_characters(char **split);
bool	ft_has_correct_color_range(char **split);
//config_content.h
void	ft_strtrim_spaces(char **split);
#endif