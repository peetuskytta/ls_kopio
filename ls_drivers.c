/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_drivers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 09:59:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 18:38:57 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_driver(t_file *arr, t_data *info, int f_count)
{
	sort_struct_array_asc(arr, f_count);
	if (info->f_time == 1)
		sort_struct_time(arr, f_count);
	if (info->f_reve == 1)
		sort_struct_reverse(arr, f_count - 1);
	if (info->arguments_on == 0)
		print_driver(arr, info, f_count);
}

void	ls_driver(t_data *info, char *name)
{
	if (info->f_recu == 1)
		ls_recursive(info, name, 0);
	else if (info->flag_count > 0)
		ls_with_flags(info, name);
	else if (info->flag_count == 0)
		no_flags(info, name);
}

void	print_driver(t_file *arr, t_data *info, int f_count)
{
	if (info->f_long == 1)
	{
		write_long_output(arr, f_count, 0);
	}
	else
		print_short(arr, f_count);
	write(1, "\n", 1);
}

void	ls_with_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;

	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NULL)
		no_directory_access((char *)path);
	if (arr != NULL)
	{
		sort_driver(arr, info, f_count);
		free(arr);
	}
}
