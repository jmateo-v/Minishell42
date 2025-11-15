/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:35:19 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 22:20:41 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*handle_dollar_case(const char *seg_value, int *j,
								char *seg_expanded, t_cli *cli)
{
	char	var[128];

	if (!seg_value[*j + 1]
		|| !(ft_isalnum((unsigned char)seg_value[*j + 1])
			|| seg_value[*j + 1] == '_' || seg_value[*j + 1] == '?'))
		return (append_literal_dollar(seg_expanded));
	(*j)++;
	parse_var_name(seg_value, j, var, sizeof(var));
	return (append_var_value(seg_expanded, var, cli));
}

static char	*handle_char_case(char *seg_expanded, char c, char *result)
{
	seg_expanded = exp_append_char(seg_expanded, c, result);
	return (seg_expanded);
}

static char	*expand_vars_loop(const char *seg_value,
								t_cli *cli, char *seg_expanded, char *result)
{
	int	j;

	j = 0;
	while (seg_value[j])
	{
		if (seg_value[j] == '$')
		{
			seg_expanded = handle_dollar_case(seg_value, &j, seg_expanded, cli);
			if (!seg_expanded)
				return (NULL);
		}
		else
		{
			seg_expanded = handle_char_case(seg_expanded, seg_value[j], result);
			if (!seg_expanded)
				return (NULL);
		}
		j++;
	}
	return (seg_expanded);
}

static char	*expand_variables_in_segment(const char *seg_value,
										t_cli *cli, char *result)
{
	char	*seg_expanded;

	seg_expanded = ft_strdup("");
	if (!seg_expanded)
	{
		cleanup(result, NULL, NULL, NULL);
		return (NULL);
	}
	seg_expanded = expand_vars_loop(seg_value, cli, seg_expanded, result);
	return (seg_expanded);
}

char	*expand_segment(t_segment *seg, t_cli *cli, char *result)
{
	char	*expanded;

	expanded = NULL;
	if (!seg->value)
		expanded = ft_strdup("");
	else if (seg->type == QUOTE_SINGLE || seg->type == QUOTE_TRANSLATION
		|| seg->type == QUOTE_LITERAL)
		expanded = ft_strdup(seg->value);
	else
		expanded = expand_variables_in_segment(seg->value, cli, result);
	return (expanded);
}
