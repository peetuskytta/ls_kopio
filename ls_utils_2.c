/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 10:16:33 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/16 17:29:58 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	save_args_stat(char **string, t_file *arr, int i)
{
	while (string[i] != NULL)
	{
		if (lstat(string[i], &arr[i].stats) == 0)
			ft_strcpy(arr[i].name, string[i]);
		else if (stat(string[i], &arr[i].stats) == 0)
			ft_strcpy(arr[i].name, string[i]);
		else
			file_no_exist(string[i]);
		i++;
	}
}

/*static void	loop_args_files(t_file *arr, t_data *info, int i)
{
	while (i < info->arg_count)
	{
		//ft_putendl("-------------LOOP_FILES");
		if (!(S_ISDIR(arr[i].stats.st_mode)))
		{

			if (info->f_long == 1 && arr[i].name[0] != '\0')
			{
				write_args_long(arr[i], info);
			}
			else if (arr[i].name[0] != '\0')
				ft_putendl(arr[i].name);
		}
		//ft_putendl("-------------LOOP_FILES");
		i++;
	}
	if (info->arg_count == 0)
		write(1, "\n", 1);
}*/

/*void	loop_directories(t_file *arr, t_data *info, int i)
{
	int	count;

	count = info->arg_count;
	info->arguments_on = 0;
//	ft_putendl("-------------LOOP_DIR");
	while (i < count)
	{
		if (S_ISDIR(arr[i].stats.st_mode))
		{
			if (permission_check(&arr[i].stats) == 1)
			{
				if (info->arg_count > 1)
				{
					print_dirname(arr[i].name);
					write(1, "\n", 1);
				}
				ls_driver(info, arr[i].name);
			}
			else if (ft_strcmp(arr[i].name, ".") != 0 && ft_strcmp(arr[i].name, "..") != 0)
			{
				write(1, "\n", 1);
				if (info->arg_count > 0)
				{
					print_dirname(arr[i].name);
					write(1, "\n", 1);
				}
				no_directory_access(arr[i].name);
			}
		}
		i++;
//		ft_putendl("-------------LOOP_DIR");
	}
}*/

void	ls_driver(t_data *info, char *name)
{
	//useful(info);
	if (info->f_recu == 1)
	{
		ls_recursive(info, name, 0);
	}
	else if (info->flag_count > 0)
	{
		ls_with_flags(info, name);
		//write(1, "\n", 1);
	}
	else if (info->flag_count == 0)
	{
		no_flags(info, name);
		//write(1, "\n", 1);
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
	//char	path[1024];
	int	i;

	i = 0;
	//ft_strclr(path);
	info->arguments_on = 1;
	arr = ft_memalloc(sizeof(t_file) * info->arg_count);
	save_args_stat(string, arr, 0);
	sort_driver(arr, info, info->arg_count);
	while (info->arg_count > i)
	{
		if (!(S_ISDIR(arr[i].stats.st_mode)))
		{
			if (info->f_long == 1 && arr[i].name[0] != '\0' && (!(S_ISLNK(arr[i].stats.st_mode))))
			{
				write_args_long(arr[i], info);
			}
			else if (arr[i].name[0] != '\0')
			{
				if (info->f_long == 1 && S_ISLNK(arr[i].stats.st_mode))
					write_args_long(arr[i], info);
				else if (info->f_long != 1 && !(S_ISLNK(arr[i].stats.st_mode)))
					ft_putendl(arr[i].name);
			}
		}
		i++;
	}
	i = 0;
	while (info->arg_count > i)
	{
		if (S_ISDIR(arr[i].stats.st_mode) || (S_ISLNK(arr[i].stats.st_mode) && info->f_long != 1))
		{
			if (info->arg_count > 1 && i != 0)
			{
				ft_putendl("");
			}
			ft_putstr(arr[i].name);
			ft_putendl(":");
			info->arguments_on = 0;
			ls_driver(info, arr[i].name);
		}
		i++;
	}
	//loop_args_files(arr, info, 0);
	//loop_directories(arr, info, 0);
	//ft_putendl("\n-------------STORE_&_PROCESS");
	free(arr);
}
