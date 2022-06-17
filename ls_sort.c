/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:04:29 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 13:36:01 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap_struct(t_file *first, t_file *second)
{
	t_file	temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

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
			if (arr[i].stats.st_mtime < arr[ii].stats.st_mtime)
				swap_struct(&arr[i], &arr[ii]);
			else if (ft_strcmp(arr[i].name, arr[ii].name) > 0)
				swap_struct(&arr[i], &arr[ii]);
			ii++;
		}
		i++;
	}
}
