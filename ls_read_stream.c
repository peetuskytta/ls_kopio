/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read_stream.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 19:53:17 by pskytta           #+#    #+#             */
/*   Updated: 2022/05/30 19:53:17 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_data	*dir_stream_all(const char *dirname, t_data *arr, int i)
{
	DIR				*dir;
	t_data			*f;
	struct dirent	*entity;

	arr->file_count = count_entries(dirname, 0);
	f = ft_memalloc(arr->file_count * sizeof(t_data));
	f = arr;
	dir = opendir(dirname);
	if (dir == NULL)
		perror("opendir() failed");
	entity = readdir(dir);
	while (entity != NULL)
	{
		f[i] = store_data(entity, f[i]);
		entity = readdir(dir);
		i++;
	}
	closedir(dir);
	return (f);
}

t_data	*dir_stream(const char *dirname, t_data *arr, int i)
{
	DIR				*dir;
	t_data			*f;
	struct dirent	*entity;

	arr->file_count = dot_count(dirname);
	f = ft_memalloc(arr->file_count * sizeof(t_data));
	f = arr;
	dir = opendir(dirname);
	if (dir == NULL)
		perror("opendir() failed");
	entity = readdir(dir);
	while (entity != NULL)
	{
		if (entity->d_name[0] != '.')
			f[i] = store_data(entity, f[i]);
		entity = readdir(dir);
		i++;
	}
	closedir(dir);
	return (f);
}

int	dot_count(const char *dir)
{
	DIR				*d;
	struct dirent	*entity;
	int				count;

	d = opendir(dir);
	if (d == NULL)
		perror("opendir() failed");
	entity = readdir(d);
	while (entity != NULL)
	{
		if (entity->d_name[0] != '.')
			count++;
		entity = readdir(d);
	}
	closedir(d);
	return (count - 1);
}

int	count_entries(const char *dirname, int count)
{
	DIR				*d;
	struct dirent	*entity;

	d = opendir(dirname);
	if (d == NULL)
		perror("opendir() failed");
	entity = readdir(d);
	while (entity != NULL)
	{
		entity = readdir(d);
		count++;
	}
	closedir(d);
	return (count);
}