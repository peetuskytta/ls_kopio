/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read_dir_stream.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:03:35 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 14:42:23 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Reads file or link data to the buf stats. Saves link path also.
**	This is where all the long format output information is stored.
*/
static void	read_stat_and_lstat(char *name, unsigned char type, t_file *file)
{
	ft_memset(file->link_path, 0, 4096);
	if (type & DT_LNK)
	{
		lstat(name, &file->stats);
		readlink(name, file->link_path, file->stats.st_size);
	}
	else
		stat(name, &file->stats);
}

static void	path_maker(char *path, const char *name)
{
	ft_strcat(path, "/");
	ft_strcat(path, name);
}

static void	clear_and_rename_path(char *path, const char *name)
{
	ft_memset(path, '\0', ft_strlen(path));
	ft_strcat(path, name);
}

/*
**	Counter returning the number of files in a folder which is used
**	to allocate enough space for the array of structs.
*/
int	file_count(t_data *info, const char *name)
{
	DIR				*d;
	struct dirent	*entity;
	int				count;

	count = 0;
	d = opendir(name);
	if (d == NULL)
		return (0);
	entity = readdir(d);
	while (entity != NULL)
	{
		if (entity->d_name[0] != '.' || \
			(entity->d_name[0] == '.' && info->f_all == 1))
			count++;
		entity = readdir(d);
	}
	closedir(d);
	return (count);
}

/*
**	Opens directory stream with "const char *name", allocates space for each entry
**	in the stream and stores the file data. Returns an array of structs each
**	representing on entry (file, directory, link, device, etc ...).
*/
t_file	*read_dir_stream(t_data *info, const char *name, int i, int f_count)
{
	t_file	*f;
	char	path[MAX_PATH];

	clear_and_rename_path(path, name);
	info->dir = opendir(name);
	if (info->dir == NULL)
		return (NO_ACCESS);
	f = (t_file *)malloc(sizeof(t_file) * f_count);
	allocation_check(info, f, "---> read_dir_stream():\n");
	info->ent = readdir(info->dir);
	while (info->ent)
	{
		if (info->ent->d_name[0] != '.' || \
			(info->ent->d_name[0] == '.' && info->f_all == 1))
		{
			ft_strcpy(f[i].name, info->ent->d_name);
			path_maker(path, f[i].name);
			read_stat_and_lstat(path, info->ent->d_type, &f[i++]);
			clear_and_rename_path(path, name);
		}
		info->ent = readdir(info->dir);
	}
	closedir(info->dir);
	return (f);
}
