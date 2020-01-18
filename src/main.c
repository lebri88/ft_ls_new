/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geliz <geliz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:42:40 by geliz             #+#    #+#             */
/*   Updated: 2020/01/18 20:46:33 by geliz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_delete_lists(t_fin *first)
{
	t_fin	*temp;
	
	while (first != NULL)
	{
//		ft_printf("\ndir = %s, name = %s\n", first->dir, first->name);
		if (first->dir)
			ft_strdel(&first->dir);
		if (first->name)
			ft_strdel(&first->name);
		temp = first->next;
		first->next = NULL;
		first->type = 0;
		free(first);
		first = temp;
	}
}

t_fin	*ft_create_next_t_fin(t_fin *temp)
{
	t_fin			*new;

	new = malloc(sizeof(t_fin));/*здесь может быть ft_memalloc*/
	new->dir = ft_strdup(temp->dir);
	new->name = NULL;
	new->type = -1;
	new->next = NULL;
	temp->next = new;
	return (new);
}

void	ft_is_it_prev_cur_dir(t_fin *temp)
{
	if (ft_strlen(temp->name) == 1 && temp->name[0] == '.')
		temp->type = 2;
	if (ft_strlen(temp->name) == 2 && temp->name[0] == '.' && temp->name[1] == '.')
		temp->type = 2;
	if (temp->name[0] == '.')
		temp->type = 2;/*hidden files*/
}

void	ft_read_dir_cycle(DIR *dir, t_fin *first)
{
	struct dirent	*entry;
	struct stat		buff;
//	t_fin			*temp;
	char			*t;

//	temp = first;
//	ft_printf("%s\n", first->dir);
	while ((entry = readdir(dir)) != NULL)
	{
		t = ft_strjoin_arg("%s %s %s", first->dir, "/", entry->d_name);
		if (stat(t, &buff) != 0)
			break;
//		ft_printf("\nentry = *%s*, %uc\n", entry->d_name, entry->d_type);
		if (entry->d_namlen > 0)
			first->name = ft_strdup(entry->d_name);
		first->type = buff.st_mode & S_IFDIR ? 1 : 0;
		ft_is_it_prev_cur_dir(first);
		first->next = ft_create_next_t_fin(first);
		first = first->next;
		ft_strdel(&t);
	}

}

int		ft_open_and_read_dir(char *cur)
{
	DIR				*dir;
	t_fin			*first;
//	t_fin			*temp;

	if (cur == NULL)
		return (0);
	first = malloc(sizeof(t_fin));
	first->dir = ft_strdup(cur);
	dir = opendir(cur);
	ft_read_dir_cycle(dir, first);
	ft_sort_t_fin(first);
	ft_print_dir(first);
	ft_recursive_call(first);
	ft_delete_lists(first);
	closedir(dir);
	return (0);
}

int		main(void)
{
	char	*curdir;
	int		res;

	if (!(curdir = ft_strdup("/")))
		return (0);
	res = ft_open_and_read_dir(curdir);
	ft_strdel(&curdir);
	return (0);
}