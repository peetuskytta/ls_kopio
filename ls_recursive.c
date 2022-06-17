/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:04:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 15:31:01 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recurse_path_maker(char *path, const char *name, char *file)
{
	ft_strclr(path);
	ft_strcat(path, name);
	ft_strcat(path, "/");
	ft_strcat(path, file);
	write(1, "\n", 1);
	ft_putstr(path);
	ft_putendl(":");
}

void	ls_recursive(t_data *info, const char *name, int i)
{
	t_file	*arr;
	char	path[PATH_MAX];
	int		f_count;

	f_count = file_count(info, name);
	arr = read_dir_stream(info, name, 0, f_count);
	if (arr == NULL)
		no_directory_access((char *)name);
	if (f_count != 0)
		sort_driver(arr, info, f_count);
	while (i < f_count)
	{
		if (S_ISDIR(arr[i].stats.st_mode))
		{
			if (ft_strcmp(arr[i].name, ".") != 0 && \
				ft_strcmp(arr[i].name, "..") != 0)
			{
				recurse_path_maker(path, name, arr[i].name);
				ls_recursive(info, path, 0);
				ft_strclr(path);
			}
		}
		i++;
	}
	free(arr);
}

void	ls_with_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;

	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NULL)
		no_directory_access((char *)path);
	sort_driver(arr, info, f_count);
	free(arr);
}
