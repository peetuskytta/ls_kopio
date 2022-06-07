/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:52:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/07 16:15:40 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	clear_and_rename_path(char *path, const char *name)
{
	ft_strclr(path);
	ft_strcat(path, name);
}

void	path_maker(char *path, const char *name)
{
	ft_strcat(path, "/");
	ft_strcat(path, name);
}

void	swap_struct(t_file *first, t_file *second)
{
	t_file	temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

void	recurse_path_maker(char *path, const char *name, char *file)
{
	ft_strclr(path);
	ft_strcat(path, name);
	ft_strcat(path, "/");
	ft_strcat(path, file);
	ft_putendl("");
	ft_putendl("");
	ft_putstr(path);
	ft_putendl(":");
}

void	save_padding(t_file *arr, t_data *info, int i, int f_count)
{
	while (f_count > i)
	{
		if (i == 0)
		{
			info->padding[0] = arr[i].stats.st_nlink;
			info->padding[1] = arr[i].stats.st_size;
			info->padding[2] = arr[i].len;
		}
		i++;
		if (arr[i].stats.st_nlink > arr[i - 1].stats.st_nlink)
			info->padding[0] = arr[i].stats.st_nlink;
		if (arr[i].stats.st_size > arr[i - 1].stats.st_size)
			info->padding[1] = arr[i].stats.st_size;
		if (arr[i].len > arr[i - 1].len)
			info->padding[1] = arr[i].len;
	}
	info->padding[0] = ft_nblen(info->padding[0]) + 1;
	info->padding[1] = ft_nblen(info->padding[1]) + 3;
	info->padding[2] = ft_nblen(info->padding[2]) + 1;
}
