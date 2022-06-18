/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:05:23 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/18 05:55:29 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_short(t_file *arr, int f_count)
{
	int	i;

	i = 0;
	while (i < f_count)
	{
		ft_putstr(arr[i].name);
		if (i != f_count - 1)
			write(1, "\n", 1);
		i++;
	}
}

void	print_from_string(char *str, int start, int n)
{
	char	*temp;

	temp = str;
	while (n > 0)
	{
		write(1, &temp[start], 1);
		start++;
		n--;
	}
	write(1, " ", 1);
}

void	count_files_directories(t_file *arr, t_data *info, int i)
{
	while (i < info->arg_count)
	{
		if (arr[i].file_ok == TRUE)
		{
			if (S_ISDIR(arr[i].stats.st_mode))
				info->f_d_count[0]++;
			if (!(S_ISDIR(arr[i].stats.st_mode)))
				info->f_d_count[1]++;
		}
		i++;
	}
}

void	space_after_str(char *str)
{
	ft_putstr(str);
	ft_putstr(" ");
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
