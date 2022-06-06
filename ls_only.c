/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:06:41 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/06 21:20:49 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	write_and_free(t_file *arr, t_data *info, int i)
{
	int	index;

	index = i;
	sort_list_ascending(info->list, i);
	i = 0;
	while (info->list[i] != NULL)
	{
		ft_putendl(info->list[i]);
		i++;
	}
	ft_free_array(index, info->list);
	free(arr);
}

void	ls_only(t_data *info, int i)
{
	t_file			*arr;
	DIR				*dir;
	struct dirent	*ent;

	info->file_count = file_count(info);
	arr = ft_memalloc(sizeof(t_file));
	dir = opendir(".");
	if (dir == NULL)
		strerror(errno);
	info->list = ft_memalloc(sizeof(char *) * info->file_count + 1);
	ent = readdir(dir);
	while (ent != NULL)
	{
		if (ent->d_name[0] != '.')
		{
			info->list[i] = ft_strdup(ent->d_name);
			i++;
		}
		ent = readdir(dir);
	}
	closedir(dir);
	info->list[i] = NULL;
	write_and_free(arr, info, i);
}
