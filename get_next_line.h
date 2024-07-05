/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vszpiech <vszpiech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 11:50:09 by vszpiech          #+#    #+#             */
/*   Updated: 2024/07/05 15:11:36 by vszpiech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
	char *get_next_line(int fd);
	void	ft_bzero(void *s, size_t n);
	void	*ft_calloc(size_t count, size_t size);
char	*ft_strcat(char *dest, char *src);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(int size, char **strs, char *sep);


#endif