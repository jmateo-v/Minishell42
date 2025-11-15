/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:58:52 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 22:19:56 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_var_name(const char *seg_value, int *j, char *var, int var_size)
{
	int	vi;

	vi = 0;
	if (seg_value[*j] == '?')
	{
		var[vi++] = '?';
		(*j)++;
	}
	else
	{
		while (seg_value[*j] && (ft_isalnum((unsigned char)seg_value[*j])
				|| seg_value[*j] == '_'))
		{
			if (vi < var_size - 1)
				var[vi++] = seg_value[(*j)++];
			else
				(*j)++;
		}
	}
	(*j)--;
	var[vi] = '\0';
}

char	*exp_append_char(char *seg_expanded, char c, char *result)
{
	char	one[2];
	char	*tmp;

	one[0] = c;
	one[1] = '\0';
	tmp = ft_strjoin(seg_expanded, one);
	free(seg_expanded);
	if (!tmp)
	{
		cleanup(result, NULL, NULL, NULL);
		return (NULL);
	}
	return (tmp);
}

char	*append_literal_dollar(char *seg_expanded)
{
	char	*tmp;

	tmp = ft_strjoin(seg_expanded, "$");
	free(seg_expanded);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*append_var_value(char *seg_expanded, const char *var, t_cli *cli)
{
	char	*val;
	char	*tmp;

	val = ft_expand_var(var, *cli->env, cli);
	if (!val)
		val = ft_strdup("");
	tmp = ft_strjoin(seg_expanded, val);
	free(seg_expanded);
	free(val);
	if (!tmp)
		return (NULL);
	return (tmp);
}
