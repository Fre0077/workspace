/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fre007 <fre007@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:53:37 by fre007            #+#    #+#             */
/*   Updated: 2025/03/13 21:30:05 by fre007           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clear_2_node(t_words **tmp, t_words **first, t_data *data)
{
	char	*ret;
	t_words	*tmp_first;

	tmp_first = *first;
	if ((*tmp) == (*first))
		(*first) = (*first)->next;
	(*tmp) = remove_node_words(*tmp, tmp_first);
	ret = ft_strdup((*tmp)->word);
	if (ret == NULL)
		ft_exit(data, 1);
	tmp_first = *first;
	if ((*tmp) == (*first))
		(*first) = (*first)->next;
	(*tmp) = remove_node_words(*tmp, tmp_first);
	if (!ft_strncmp("<<", data->find, 3))
		return (ret);
	return (dollar_manager_stupid(ret, data));
}

char	*clear_next_node(t_words **tmp, char *finded, t_words **first,
							t_data *data)
{
	char	*ret;
	t_words	*tmp_first;

	tmp_first = *first;
	ret = ft_strdup((*tmp)->next->word);
	if (ret == NULL)
		ft_exit(data, 1);
	remove_node_words((*tmp)->next, tmp_first);
	(*tmp)->word = remove_finded((*tmp)->word, finded, data);
	if (!ft_strncmp("<<", data->find, 3))
		return (ret);
	return (dollar_manager_stupid(ret, data));
}

char	*clear_this_node(t_words **tmp, char *finded, t_words **first,
							t_data *data)
{
	char	*ret;
	t_words	*tmp_first;

	tmp_first = *first;
	ret = ft_strdup(finded);
	if (ret == NULL)
		ft_exit(data, 1);
	if ((*tmp) == (*first))
		(*first) = (*tmp)->next;
	(*tmp) = remove_node_words(*tmp, tmp_first);
	if (!ft_strncmp("<<", data->find, 3))
		return (ret);
	return (dollar_manager_stupid(ret, data));
}

char	*remove_last_part(t_words **tmp, char *finded, char *find, t_data *data)
{
	char	*ret;

	ret = ft_strdup(&finded[ft_strlen(find)]);
	if (ret == NULL)
		ft_exit(data, 1);
	(*tmp)->word = remove_finded((*tmp)->word, finded, data);
	if (!ft_strncmp("<<", data->find, 3))
		return (ret);
	return (dollar_manager_stupid(ret, data));
}
