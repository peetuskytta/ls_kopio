/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read_dir_stream.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:47:39 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/15 11:24:25 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	read_stat_and_lstat(char *name, unsigned char type, t_file *data)
{
	if (type & DT_LNK)
		lstat(name, &data->stats);
	else
		stat(name, &data->stats);
}

static void	path_maker(char *path, const char *name)
{
	ft_strcat(path, "/");
	ft_strcat(path, name);
}

static void	clear_and_rename_path(char *path, const char *name)
{
	ft_strclr(path);
	ft_strcat(path, name);
}

/*
**	Opens directory stream to count how many entries there are
**	in a given directory. Returns and integer representing the
**	number of files/directories/links etc in the given directory.
*/
t_file	*read_dir_stream(t_data *info, const char *name, int i, int f_count)
{
	t_file	*f;
	char	path[1024];

	clear_and_rename_path(path, name);
	f = ft_memalloc(sizeof(t_file) * f_count);
	info->dir = opendir(name);
	if (info->dir == NULL)
		return (NULL);
	info->ent = readdir(info->dir);
	while (info->ent)
	{
		if (info->ent->d_name[0] != '.' || \
			(info->ent->d_name[0] == '.' && info->f_all == 1))
		{
			ft_strcpy(f[i].name, info->ent->d_name);
			f[i].len = info->ent->d_namlen;
			path_maker(path, f[i].name);
			read_stat_and_lstat(path, info->ent->d_type, &f[i]);
			clear_and_rename_path(path, name);
			i++;
		}
		info->ent = readdir(info->dir);
	}
	closedir(info->dir);
	return (f);
}
