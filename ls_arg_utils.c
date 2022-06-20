/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_arg_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:06:46 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/20 18:22:08 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Function that saves important information: stat, lstat, if file exist
**	or not, and how many non-exist files arguments contain.
*/
static void	save_args_stat(char **string, t_file *arr, int i)
{
	while (string[i] != NULL)
	{
		if (lstat(string[i], &arr[i].stats) == 0)
		{
			ft_strcpy(arr[i].name, string[i]);
			readlink(arr[i].name, arr[i].link_path, arr[i].stats.st_size);
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

/*
**	Loops the argument files and acts only on non directory && existing files.
**	Break when number of existing files have been reached.
*/
static void	loop_files(t_data *info, t_file *arr, int i)
{
	int	count;

	count = info->f_d_count[1];
	while (info->arg_count > i)
	{
		if (!(S_ISDIR(arr[i].stats.st_mode)) && arr[i].file_ok == TRUE)
		{
			if (info->f_long == 1 && (!(S_ISLNK(arr[i].stats.st_mode))))
				write_args_long(arr[i]);
			else
			{
				if (info->f_long == 1 && S_ISLNK(arr[i].stats.st_mode))
					write_args_long(arr[i]);
				else if (info->f_long == 0 && !(S_ISLNK(arr[i].stats.st_mode)))
					ft_putendl(arr[i].name);
				else
					ft_putendl(arr[i].name);
			}
			if ((!(S_ISDIR(arr[i].stats.st_mode)) && arr[i].file_ok == TRUE))
				count--;
		}
		i++;
		if (count == 0)
			break ;
	}
}

/*
**	Loops through the arguments which are directories and acts on them.
*/
static void	loop_directories(t_data *info, t_file *arr, int i)
{
	int	count;

	count = info->f_d_count[0];
	while (info->arg_count > i)
	{
		if ((S_ISDIR(arr[i].stats.st_mode) && arr[i].file_ok == TRUE))
		{
			if (info->arg_count > 1)
			{
				ft_putstr(arr[i].name);
				ft_putendl(":");
			}
			info->arguments_on = 0;
			ls_driver(info, arr[i].name);
			if (count != 1)
				write(1, "\n", 1);
			count--;
		}
		if (count == 0)
			break ;
		i++;
	}
}

/*
**	Handles one argument cases only (with or without flags).
*/
static void	ls_one_arg_only(t_file *arr, t_data *info)
{
	info->arguments_on = 0;
	if (S_ISDIR(arr[0].stats.st_mode) && arr[0].file_ok == TRUE)
	{
		ls_driver(info, arr[0].name);
		if (info->flag_count == 0 && arr[0].stats.st_mode & X_OK)
			write(1, "\n", 1);
	}
	else if (arr[0].file_ok == TRUE)
	{
		if (info->f_long == 1)
			write_args_long(arr[0]);
		else
			ft_putendl(arr[0].name);
	}
	free(arr);
	free(info);
	exit(0);
}

/*
**	Stores and processes the arguments using the functions above.
*/
void	store_and_process_arguments(char **string, t_data *info)
{
	t_file	*arr;

	info->arguments_on = 1;
	arr = (t_file *)malloc(sizeof(t_file) * info->arg_count);
	save_args_stat(string, arr, 0);
	sort_driver(arr, info, info->arg_count);
	count_files_directories(arr, info, 0);
	if (info->arg_count == 1)
		ls_one_arg_only(arr, info);
	loop_files(info, arr, 0);
	if (info->f_d_count[1] > 0 && info->f_d_count[0] > 0)
		write(1, "\n", 1);
	loop_directories(info, arr, 0);
	free(arr);
}
