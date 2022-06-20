/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:04:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/20 14:38:19 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Pathmaker function specific for recursive flag. Also outputs the path.
*/
static void	recurse_path_maker(char *path, const char *name, char *file)
{
	ft_strclr(path);
	ft_strcat(path, name);
	if (ft_strcmp(name, "/") != 0)
		ft_strcat(path, "/");
	ft_strcat(path, file);
	write(1, "\n", 1);
	ft_putstr(path);
	ft_putendl(":");
}

/*
**	Recursive function to handle new folders inside the directory
**	stream opened.
*/
void	ls_recursive(t_data *info, const char *name, int i)
{
	t_file	*arr;
	char	path[MAX_PATH];
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
