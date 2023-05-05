/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariaavoletta <mariaavoletta@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:06:14 by marioliv          #+#    #+#             */
/*   Updated: 2023/05/05 09:35:50 by mariaavolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*maria(int fd, char *buffer, char *backup);
char	*get_next_line(int fd);
char	*looping(char *line);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memset(void *s, int a, size_t n);
void	ft_bzero(void *s, size_t n);


# endif