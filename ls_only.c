/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:02:39 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/20 15:13:00 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Writes simple ls commands with no flags or whatsoever.
*/
static void	write_ls_only(t_file *arr, int f_count)
{
	int	i;

	i = 0;
	sort_struct_array_asc(arr, f_count);
	while (i < f_count)
	{
		ft_putstr(arr[i].name);
		if (i != f_count - 1)
			write(1, "\n", 1);
		i++;
	}
}

/*
**	Function that takes a path and opens a directory stream.
**	In case of NULL return it outputs permission denied message.
*/
void	no_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;
	char	*strname;

	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NULL)
	{
		strname = ft_strrchr(path, '/');
		no_directory_access(++strname);
	}
	else
	{
		write_ls_only(arr, f_count);
		if (info->arg_count > 1)
			write(1, "\n", 1);
		free(arr);
	}
}

void	print_links_nbr(struct stat *stats)
{
	ft_putnbr(stats->st_nlink);
	ft_putchar(' ');
}

void	space_after_nbr(int nbr)
{
	ft_putnbr(nbr);
	ft_putchar(' ');
}
