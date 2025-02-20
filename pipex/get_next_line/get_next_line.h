/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-sant <fde-sant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:16:16 by fde-sant          #+#    #+#             */
/*   Updated: 2024/11/30 11:35:03 by fde-sant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

int		check_buffer(char *buffer, int check_case);
int		buffer_size(char *buffer, char *join);

char	*return_buffer(char **buffer);

void	next_buffer(char **buffer, int i);
void	join_buffer(char *buffer, char *temp, char *join);

#endif