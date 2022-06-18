/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read_dir_stream.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:03:35 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/18 08:49:55 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Reads file or link data to the buf stats. This is where all the long
**	format output information is stored.
*/
static void	read_stat_and_lstat(char *name, unsigned char type, t_file *data)
{
	if (type & DT_LNK)
		lstat(name, &data->stats);
	else
		stat(name, &data->stats);
}

/*
**	Simple pathmaker function.
*/
static void	path_maker(char *path, const char *name)
{
	ft_strcat(path, "/");
	ft_strcat(path, name);
}

/*
**	Clears and renames the path in order to print correct info.
*/
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
	char	path[PATH_MAX];

	clear_and_rename_path(path, name);
	info->dir = opendir(name);
	if (info->dir == NULL)
		return (NULL);
	f = (t_file *)malloc(sizeof(t_file) * f_count);
	info->ent = readdir(info->dir);
	while (info->ent)
	{
		if (info->ent->d_name[0] != '.' || \
			(info->ent->d_name[0] == '.' && info->f_all == 1))
		{
			ft_strcpy(f[i].name, info->ent->d_name);
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
