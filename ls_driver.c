/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_driver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:07:03 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/06 21:31:47 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_driver(t_data *info, char *dirname)
{
	if (info->flag_count == 0)
		ls_only(info, 0);
	if (info->f_recu == 1)
		ls_recursive(info, dirname, 0);
	else
		ls_with_flags(info);
}

void	sort_driver(t_file *arr, t_data *info)
{
	sort_struct_array_asc(arr, info->file_count);
	if (info->f_time == 1)
		sort_struct_time(arr, info->file_count);
	if (info->f_reve == 1)
		sort_struct_reverse(arr, info->file_count - 1);
}

t_file	*read_dir_stream(t_data *info, const char *dirname, int i)
{
	t_file	*f;

	info->file_count = file_count(info);
	f = (t_file *)malloc(sizeof(t_file) * info->file_count + 1);
	info->dir = opendir(dirname);
	if (info->dir == NULL)
		strerror(errno);
	info->ent = readdir(info->dir);
	while (info->ent)
	{
		if (info->ent->d_name[0] != '.' || \
			(info->ent->d_name[0] == '.' && info->f_all == 1))
		{
			ft_strcpy(f[i].name, info->ent->d_name);
			stat(info->ent->d_name, &f[i].stats);
			i++;
		}
		info->ent = readdir(info->dir);
	}
	closedir(info->dir);
	return (f);
}
