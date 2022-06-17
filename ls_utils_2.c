/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:06:46 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 19:22:46 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	save_args_stat(char **string, t_file *arr, int i)
{
	while (string[i] != NULL)
	{
		if (lstat(string[i], &arr[i].stats) == 0)
		{
			ft_strcpy(arr[i].name, string[i]);
			arr[i].file_ok = TRUE;
		}
		else if (stat(string[i], &arr[i].stats) == 0)
		{
			ft_strcpy(arr[i].name, string[i]);
			arr[i].file_ok = TRUE;
		}
		else
		{
			file_no_exist(string[i]);
			arr[i].file_ok = FALSE;
		}
		i++;
	}
}

static void	loop_files(t_data *info, t_file *arr, int i)
{
	while (info->arg_count > i)
	{
		if (!(S_ISDIR(arr[i].stats.st_mode)) && arr[i].file_ok == TRUE)
		{
			if (info->f_long == 1 && arr[i].name[0] != '\0' \
				&& (!(S_ISLNK(arr[i].stats.st_mode))))
			{
				write_args_long(arr[i]);
			}
			else if (arr[i].name[0] != '\0')
			{
				if (info->f_long == 1 && S_ISLNK(arr[i].stats.st_mode) && \
					info->arg_count != 0)
					write_args_long(arr[i]);
				else if (info->f_long != 1 && !(S_ISLNK(arr[i].stats.st_mode)))
					ft_putendl(arr[i].name);
			}
		}
		i++;
	}
}

static void	loop_directories(t_data *info, t_file *arr, int i)
{
	while (info->arg_count > i)
	{
		if (S_ISDIR(arr[i].stats.st_mode) || \
			(S_ISLNK(arr[i].stats.st_mode) && info->f_long))
		{
			if (info->arg_count > 1 && i != 0)
				write(1, "\n", 1);
			if (info->arg_count > 1)
			{
				ft_putstr(arr[i].name);
				ft_putendl(":");
			}
			info->arguments_on = 0;
			ls_driver(info, arr[i].name);
			if (info->arg_count > 1 && i != 0 && i != info->arg_count - 1)
				write(1, "\n", 1);
		}
		if (info->flag_count == 0)
			write(1, "\n", 1);
		i++;
	}
}

void	store_and_process_arguments(char **string, t_data *info)
{
	t_file	*arr;

	info->arguments_on = 1;
	arr = (t_file *)malloc(sizeof(t_file) * info->arg_count);
	save_args_stat(string, arr, 0);
	sort_driver(arr, info, info->arg_count);
	loop_files(info, arr, 0);
	loop_directories(info, arr, 0);
	free(arr);
}
