/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 17:00:47 by dogs              #+#    #+#             */
/*   Updated: 2025/11/14 17:18:08 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*extract_var_name(const char **p)
{
	const char	*start;

	start = *p;
	while (**p && (ft_isalnum(**p) || **p == '_'))
		(*p)++;
	return (ft_strndup(start, *p - start));
}

static char	*append_string(char *result, const char *str)
{
	char	*new_result;
	size_t	old_len;
	size_t	val_len;

	old_len = ft_strlen(result);
	val_len = ft_strlen(str);
	new_result = ft_realloc(result, old_len + 1, old_len + val_len + 1);
	if (!new_result)
		return (NULL);
	ft_strcat(new_result, str);
	return (new_result);
}

static char	*append_char(char *result, char c)
{
	size_t	old_len;
	char	*new_result;

	old_len = ft_strlen(result);
	new_result = ft_realloc(result, old_len + 1, old_len + 2);
	if (!new_result)
		return (NULL);
	new_result[old_len] = c;
	new_result[old_len + 1] = '\0';
	return (new_result);
}

static char	*expand_variable(const char **p, t_shenv *env, char *result)
{
	char	*var_name;
	char	*var_value;

	(*p)++;
	var_name = extract_var_name(p);
	var_value = ft_getenv(env, var_name);
	free(var_name);
	if (var_value)
		result = append_string(result, var_value);
	return (result);
}

char	*expand_variables(const char *input, t_shenv *env)
{
	char		*result;
	const char	*p;

	if (!input)
		return (NULL);
	result = ft_calloc(1, 1);
	p = input;
	while (*p)
	{
		if (*p == '$' && *(p + 1) && (ft_isalnum(*(p + 1)) || *(p + 1) == '_'))
			result = expand_variable(&p, env, result);
		else
		{
			result = append_char(result, *p);
			p++;
		}
	}
	return (result);
}
