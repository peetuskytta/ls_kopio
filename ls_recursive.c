/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:04:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 14:42:08 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Pathmaker function specific for recursive flag. Also outputs the path.
*/
static void	recurse_path_maker(char *path, const char *name, char *file)
{
	ft_memset(path, '\0', MAX_PATH);
	ft_strcat(path, name);
	if (ft_strcmp(name, "/") != 0)
		ft_strcat(path, "/");
	ft_strcat(path, file);
	write(1, "\n", 1);
	write(1, path, ft_strlen(path));
	write(1, ":\n", 2);
}

/*
**	Printing the correct path in case of no access.
*/
static void	recursion_no_access(char *path)
{
	char	*strname;

	strname = ft_strrchr(path, '/');
	if (strname)
		no_directory_access(++strname);
	else
		no_directory_access((char *)path);
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
	if (arr == NO_ACCESS)
		recursion_no_access((char *)name);
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
				ft_memset(path, '\0', MAX_PATH);
			}
		}
		i++;
	}
	free(arr);
}
