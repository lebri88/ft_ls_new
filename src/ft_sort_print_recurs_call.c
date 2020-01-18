/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_print_recurs_call.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 16:23:03 by geliz             #+#    #+#             */
/*   Updated: 2020/01/18 20:46:49 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_recursive_call(t_fin *first)
{
	t_fin	*temp;

	temp = first;
	while (first != NULL)
	{
		if (first->type == 1)
		{
			first->dir = ft_strjoin_arg("%f %s %s", first->dir, "/",
				first->name);
			ft_open_and_read_dir(first->dir);
		}
		first = first->next;
	}
//	ft_delete_lists(temp);
}

void	ft_print_dir(t_fin *first)
{
	size_t	len;
	t_fin	*temp;

	ft_printf("\n%s\n", first->dir);
	len = 0;
	temp = first;
	while (first->next != NULL)
	{
		if (ft_strlen(first->name) > len)
			len = ft_strlen(first->name);
		first = first->next;
	}
	len += 8;
	while (temp->next != NULL)
	{
		if (temp->type != 2)
			ft_printf("%-*s", len, temp->name);
		temp = temp->next;
	}
}

void	ft_sort_t_fin(t_fin *first)
{
	t_fin	*temp;

	temp = first;
}
