/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:23:34 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/15 17:05:43 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	recurse_path_maker(char *path, const char *name, char *file)
{
	ft_strclr(path);
	ft_strcat(path, name);
	ft_strcat(path, "/");
	ft_strcat(path, file);
	ft_putstr("\n\n");
	ft_putstr(path);
	ft_putendl(":");
}

void	perm_error(const char *name)
{
	ft_putstr("ls: ");
	ft_putstr(name);
	ft_putchar(':');
	ft_putstr(" Permission denied");

}

void	ls_recursive(t_data *info, const char *name, int i)
{
	t_file	*arr;
	char	path[1024];
	int		f_count;

	f_count = file_count(info, name);
	arr = read_dir_stream(info, name, 0, f_count);
	if (arr == NULL)
		perm_error(name);
	sort_driver(arr, info, f_count);
	while (i < f_count)
	{
		if (arr[i].stats.st_mode & S_IFDIR/*&& permission_check(&arr[i].stats) == 1*/)
		{
			if (ft_strcmp(arr[i].name, ".") != 0 && ft_strcmp(arr[i].name, "..") != 0)
			{
				recurse_path_maker(path, name, arr[i].name);
				ls_recursive(info, path, 0);
				ft_strclr(path);
			}
		}
		/*else if (arr[i].stats.st_mode & S_IFDIR)
			perm_error(name);
	*/	i++;
	}
	free(arr);
}

void	ls_with_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;

	//ft_putendl(path);
	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NULL)
		perm_error(path);
	sort_driver(arr, info, f_count);
	free(arr);
}
