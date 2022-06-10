/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:52:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/10 10:18:17 by pskytta          ###   ########.fr       */
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
			ft_putchar('\n');
		i++;
	}
	ft_putchar('\n');
}

void	space_after_str(char *str)
{
	ft_putstr(str);
	ft_putstr(" ");
}

void	print_block_total(t_file *arr, int f_count)
{
	int	i;
	int	blocks;

	i = 0;
	while (f_count > i)
	{
		blocks = blocks + arr[i].stats.st_blocks;
		i++;
	}
	ft_putstr("total ");
	ft_putnbr_endl(blocks);
}

/*
**	This functions saves three padding information:
**	1. st_nlink (length of number of links).
**	2. st_size (length of the size).
**	3. length of the name.
*/
void	save_padding(t_file *arr, t_data *info, int i, int f_count)
{
	while (f_count > i)
	{
		if (i == 0)
		{
			info->padding[0] = arr[i].stats.st_nlink;
			info->padding[1] = arr[i].stats.st_size;
			info->padding[2] = arr[i++].len;
		}
		if (arr[i].stats.st_nlink > arr[i - 1].stats.st_nlink)
			info->padding[0] = arr[i].stats.st_nlink;
		if (arr[i].stats.st_size > arr[i - 1].stats.st_size)
			info->padding[1] = arr[i].stats.st_size;
		if (arr[i].len > info->padding[2])
			info->padding[2] = arr[i].len;
		i++;
	}
	info->padding[0] = ft_nblen(info->padding[0]) + 1;
	info->padding[1] = ft_nblen(info->padding[1]) + 1;
	info->padding[2] = info->padding[2] + 3;
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
