/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogs <dogs@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 10:21:22 by dogs              #+#    #+#             */
/*   Updated: 2025/10/19 10:07:01 by dogs             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	ft_len(char *s, char *esc_char)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\\' && ft_strchr(esc_char, s[i + 1]))
			i++;
		len++;
		i++;
	}
	return (len);
}

void ft_free_str_array(char ***ptr)
{
    int i = 0;
    if (!ptr || !*ptr)
        return;
    while ((*ptr)[i])
    {
        free((*ptr)[i]);
        (*ptr)[i] = NULL;
        i++;
    }
    free(*ptr);
    *ptr = NULL;
}

char	*ft_esc_str(char *s, char *esc_char, size_t n)
{
	int		len;
	char	*r;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (n <= 0 || n > ft_strlen(s))
		return (ft_strdup(s));
	len = ft_len(s, esc_char);
	r = (char *)ft_calloc(len + 1, sizeof(char));
	if (!r)
		return (NULL);
	while (i < n)
	{
		if (s[i] == '\\' && ft_strchr(esc_char, s[i]))
			r[j] = s[++i];
		else
			r[j] = s[i];
		i++;
		j++;
	}
	return (r);
}

size_t ft_ptr_array_len(void **ptr)
{
    size_t i = 0;

    if (!ptr)
        return (0);
    while (ptr[i])
        i++;
    return (i);
}
char **ft_add_str(char **dptr, const char *ptr, int pos)
{
    int     len;
    int     i = 0;
    int     j = 0;
    char    **r;

    if (!dptr || !ptr)
        return (NULL);
    len = ft_ptr_array_len((void **)dptr);
    if (pos < 0 || pos > len)
        return (dptr);
    r = ft_calloc(len + 2, sizeof(char *));
    if (!r)
        return (NULL);
    while (j < len + 1)
    {
        if (j == pos)
            r[i++] = ft_strdup(ptr);
        if (j < len)
            r[i++] = ft_strdup(dptr[j]);
        j++;
    }
    return r;
}



