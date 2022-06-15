/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:06:41 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/15 17:08:18 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	write_ls_only(t_file *arr, int f_count)
{
	int	i;

	i = 0;
	sort_struct_array_asc(arr, f_count);
	while (i < f_count)
	{
		ft_putstr(arr[i].name);
		if (i != f_count - 1)
			ft_putendl("");
		i++;
	}
	ft_putendl("");
}

void	no_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;

	//ft_putendl(path);
	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NULL)
		perm_error(path);
	sort_struct_array_asc(arr, f_count);
	write_ls_only(arr, f_count);
	free(arr);
}


void	ls_only(t_data *info, int f_count)
{
	t_file	*f;
	int		i;

	i = 0;
	f_count = file_count(info, ".");
	f = ft_memalloc(sizeof(t_file) * f_count);
	info->dir = opendir(".");
	if (info->dir == NULL)
		perm_error(".");
	info->ent = readdir(info->dir);
	while (info->ent)
	{
		if (info->ent->d_name[0] != '.' || \
			(info->ent->d_name[0] == '.' && info->f_all == 1))
		{
			ft_strcpy(f[i].name, info->ent->d_name);
			i++;
		}
		info->ent = readdir(info->dir);
	}
	closedir(info->dir);
	write_ls_only(f, f_count);
	free(f);
}
