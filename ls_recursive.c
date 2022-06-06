/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:23:34 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/06 21:30:08 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_recursive(t_data *info, const char *dirname, int i)
{
	t_file	*arr;

	arr = read_dir_stream(info, dirname, 0);
	sort_driver(arr, info);
	ft_putstr(dirname);
	ft_putendl(":");
	print_short(arr, info);
	ft_putendl("");
	while (i < info->file_count)
	{
		if (ft_strcmp(arr[i].name, ".") != 0 && ft_strcmp(arr[i].name, "..") != 0)
		{
			if (is_directory(arr[i].stats) == 1)
			{
				path_maker(info->path, arr[i].name);
				ft_putendl(info->path);
				//ft_putendl(arr[i].name);
				ls_recursive(info, info->path, 0);
				ft_strclr(info->path);
				i++;
			}
			i++;
		}
	}
	free(arr);
}

void	path_maker(char *start, char *name)
{
	if (!(ft_strchr(start, '.')))
		ft_strcat(start, ".");
	ft_strcat(start, "/");
	ft_strcat(start, name);
}

int	is_directory(struct stat file)
{
	if (file.st_mode & S_IFDIR)
		return (1);
	return (0);
}


void	print_short(t_file *arr, t_data *info)
{
	int	i;

	i = 0;
	while (i < info->file_count)
	{
		ft_putendl(arr[i].name);
		i++;
	}
}
