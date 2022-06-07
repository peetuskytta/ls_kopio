/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:08:32 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/07 11:44:14 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_list_ascending(char **list, int n)
{
	int		i;
	int		ii;
	char	*temp;

	i = 0;
	while (i < n - 1)
	{
		ii = i + 1;
		while (ii < n)
		{
			if (ft_strcmp(list[i], list[ii]) > 0)
			{
				temp = list[i];
				list[i] = list[ii];
				list[ii] = temp;
			}
			ii++;
		}
		i++;
	}
}

void	sort_struct_array_asc(t_file *arr, int n)
{
	int		i;
	int		ii;

	i = 0;
	while (i < n - 1)
	{
		ii = i + 1;
		while (ii < n)
		{
			if (ft_strcmp(arr[i].name, arr[ii].name) > 0)
				swap_struct(&arr[i], &arr[ii]);
			ii++;
		}
		i++;
	}
}

void	sort_struct_reverse(t_file *arr, int end)
{
	int		start;

	start = 0;
	while (start < end)
	{
		swap_struct(&arr[start], &arr[end]);
		start++;
		end--;
	}
}

void	sort_struct_time(t_file *arr, int n)
{
	int	i;
	int	ii;

	i = 0;
	while (i < n - 1)
	{
		ii = i + 1;
		while (ii < n)
		{
			if (arr[i].stats.st_mtimespec.tv_sec < \
				arr[ii].stats.st_mtimespec.tv_sec)
				swap_struct(&arr[i], &arr[ii]);
			else if (ft_strcmp(arr[i].name, arr[ii].name) > 0)
				swap_struct(&arr[i], &arr[ii]);
			ii++;
		}
		i++;
	}
}

int	file_count(t_data *info, const char *name)
{
	DIR				*d;
	struct dirent	*entity;
	int				count;

	count = 0;
	d = opendir(name);
	if (d == NULL)
		return (0);
	entity = readdir(d);
	while (entity != NULL)
	{
		if (entity->d_name[0] != '.' || \
			(entity->d_name[0] == '.' && info->f_all == 1))
			count++;
		entity = readdir(d);
	}
	closedir(d);
	return (count);
}
