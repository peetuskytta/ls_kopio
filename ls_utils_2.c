/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:16:33 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/15 17:04:57 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	save_link_stat(char **string, t_file *arr, int i)
{
	while (string[i] != NULL)
	{
		if (S_ISLNK(arr[i].stats.st_mode))
			lstat(string[i], &arr[i].stats);
		i++;
	}
}

static void	save_args_stat(char **string, t_file *arr, int i)
{
	while (string[i] != NULL)
	{
		if (stat(string[i], &arr[i].stats) != 0)
		{
			//ft_putendl(string[i]);
			file_no_exist(string[i]);
		}
		else
			ft_strcpy(arr[i].name, string[i]);
		i++;
	}
}

static void	loop_args_files(t_file *arr, t_data *info, int i)
{
	while (i < info->arg_count)
	{
		if (!(S_ISDIR(arr[i].stats.st_mode)))
		{
			if (info->f_long == 1 && arr[i].name[0] != '\0')
				write_args_long(arr[i], info);
			else if (arr[i].name[0] != '\0')
				ft_putendl(arr[i].name);
		}
		i++;
	}
	//ft_putchar('\n');
}

void	loop_directories(t_file *arr, t_data *info, int i)
{
	int	count;

	count = info->arg_count;
	info->arguments_on = 1;
	info->arg_count = 0;
	info->nb_of_args = 0;
	while (i < count)
	{
		if (S_ISDIR(arr[i].stats.st_mode))
		{
			if (permission_check(&arr[i].stats) == 1)
			{
				useful(info);
				print_dirname(arr[i].name);
				ls_driver(info, info->list, arr[i].name);
			}
			else
				no_directory_access(arr[i].name);
		}
		i++;
	}
}

int	permission_check(struct stat *stats)
{
	if (S_IXUSR & stats->st_mode)
		return (1);
	else
		return (0);
}

void	store_and_process_arguments(char **string, t_data *info)
{
	t_file	*arr;

	info->arguments_on = 1;
	useful(info);
	arr = ft_memalloc(sizeof(t_file) * info->arg_count);
//	ft_putendl(string[0]);
//	ft_putendl(string[1]);
//	ft_putendl(string[2]);
//	ft_putendl(string[3]);
	save_args_stat(string, arr, 0);
	save_link_stat(string, arr, 0);
	sort_driver(arr, info, info->arg_count);
	loop_args_files(arr, info, 0);
	loop_directories(arr, info, 0);
	free(arr);
}
