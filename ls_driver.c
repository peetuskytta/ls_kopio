/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_driver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:07:03 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/07 16:13:41 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_driver(t_data *info)
{
	if (info->flag_count == 0)
		ls_only(info, 0);
	else if (info->f_recu == 1)
		ls_recursive(info, ".", 0);
	else
		ls_with_flags(info, ".");
}

void	sort_driver(t_file *arr, t_data *info, int f_count)
{
	sort_struct_array_asc(arr, f_count);
	if (info->f_time == 1)
		sort_struct_time(arr, f_count);
	if (info->f_reve == 1)
		sort_struct_reverse(arr, f_count - 1);
	save_padding(arr, info, 0, f_count);
	print_short(arr, info, f_count);
	//ft_putendl("");
}

t_file	*read_dir_stream(t_data *info, const char *name, int i, int f_count)
{
	t_file	*f;
	char	path[1024];

	clear_and_rename_path(path, name);
	f = ft_memalloc(sizeof(t_file) * f_count);
	info->dir = opendir(name);
	if (info->dir == NULL)
		strerror(errno);
	info->ent = readdir(info->dir);
	while (info->ent)
	{
		if (info->ent->d_name[0] != '.' || \
			(info->ent->d_name[0] == '.' && info->f_all == 1))
		{
			ft_strcpy(f[i].name, info->ent->d_name);
			f[i].len = info->ent->d_namlen;
			path_maker(path, f[i].name);
			stat(path, &f[i].stats);
			clear_and_rename_path(path, name);
			i++;
		}
		info->ent = readdir(info->dir);
	}
	closedir(info->dir);
	return (f);
}
