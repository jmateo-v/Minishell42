/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmateo-v <jmateo-v@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:19:13 by jmateo-v          #+#    #+#             */
/*   Updated: 2025/10/06 13:47:59 by jmateo-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>

char	*get_next_line(int fd);
char	*gnl_strchr(const char *str, int c);
size_t	gnl_strlen(const char *c);
char	*gnl_strjoin(char *s1, char const *s2);
char	*gnl_strdup(const char *str);
char	*extract_line(char *stash);
char	*update_stash(char *stash);
char	*read_and_update_stash(int fd, char *stash, char *buffer);

#endif
