/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:06:41 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/07 15:16:45 by pskytta          ###   ########.fr       */
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
	t_file	*arr;
	int		count;

	count = file_count(info, ".");
	arr = ft_memalloc(sizeof(t_file));
	info->dir = opendir(".");
	if (info->dir == NULL)
		strerror(errno);
	info->list = ft_memalloc(sizeof(char *) * count);
	info->ent = readdir(info->dir);
	while (info->ent != NULL)
	{
		if (info->ent->d_name[0] != '.')
		{
			info->list[i] = ft_strdup(info->ent->d_name);
			i++;
		}
		info->ent = readdir(info->dir);
	}
	closedir(info->dir);
	info->list[i] = NULL;
	write_and_free(arr, info, i);
}
