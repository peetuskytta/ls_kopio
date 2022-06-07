/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:23:34 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/07 16:13:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_recursive(t_data *info, const char *name, int i)
{
	t_file	*arr;
	char	path[1024];
	int		f_count;

	f_count = file_count(info, name);
	arr = read_dir_stream(info, name, 0, f_count);
	sort_driver(arr, info, f_count);
	while (i < f_count)
	{
		if (arr[i].stats.st_mode & S_IFDIR)
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

void	print_short(t_file *arr, t_data *info, int f_count)
{
	int	i;

	i = 0;

	while (i < f_count)
	{
		//ft_putnbr(arr[i].len);
		//ft_putstr(" ");
		ft_putstr(arr[i].name);
		if (i != f_count - 1)
			ft_putendl("");
		i++;
	}
	ft_strclr(info->empty);
}

void	ls_with_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;

	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	sort_driver(arr, info, f_count);
	free(arr);
}
