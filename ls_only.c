/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:02:39 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 14:14:33 by pskytta          ###   ########.fr       */
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
		write(1, arr[i].name, ft_strlen(arr[i].name));
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

	strname = NULL;
	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NO_ACCESS && path)
	{
		strname = ft_strrchr(path, '/');
		if (strname)
			no_directory_access(++strname);
		else
			no_directory_access((char *)path);
	}
	else
	{
		if (!(path))
			no_directory_access(strname);
		write_ls_only(arr, f_count);
		if (info->arg_count > 1)
			write(1, "\n", 1);
		free(arr);
	}
}

void	print_links_nbr(struct stat *stats)
{
	ft_putnbr(stats->st_nlink);
	write(1, " ", 1);
}

void	space_after_nbr(int nbr)
{
	ft_putnbr(nbr);
	write(1, " ", 1);
}
