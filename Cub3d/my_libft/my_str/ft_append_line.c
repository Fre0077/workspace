/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 10:53:10 by alborghi          #+#    #+#             */
/*   Updated: 2025/03/13 22:25:09 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_append_line(char **map, char *line)
{
	char	**new_map;
	int		i;

	if (line == NULL)
		return (map);
	i = 0;
	while (map && map[i])
		i++;
	new_map = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new_map)
		return (ft_free_mat_char(map), NULL);
	i = 0;
	while (map && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(map);
	return (new_map);
}
