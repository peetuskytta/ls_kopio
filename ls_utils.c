/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:05:23 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 18:41:59 by pskytta          ###   ########.fr       */
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

	blocks = 0;
	i = 0;
	while (f_count > i)
	{
		blocks = blocks + arr[i].stats.st_blocks;
		i++;
	}
	if (f_count != 0)
	{
		ft_putstr("total ");
		ft_putnbr_endl(blocks);
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

int	return_major_or_minor(int rdev, int option)
{
	if (option == 1)
		return (((int32_t)(((u_int32_t)(rdev) >> 24) & 0xff)));
	else
		return (((int32_t)((rdev) & 0xffffff)));
}
