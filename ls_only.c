/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_only.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:06:41 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/16 17:18:10 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	write_ls_only(t_file *arr, int f_count)
{
	int	i;

	i = 0;
	//ft_putendl("LOLOLOLLOLOL");
	sort_struct_array_asc(arr, f_count);
	while (i < f_count)
	{
		ft_putstr(arr[i].name);
		if (i != f_count - 1)
			write(1, "\n", 1);
		i++;
	}
}

void	no_flags(t_data *info, const char *path)
{
	t_file	*arr;
	int		f_count;

	//ft_putendl("-------------------LOLOLOLO");
	f_count = file_count(info, path);
	arr = read_dir_stream(info, path, 0, f_count);
	if (arr == NULL)
		no_directory_access((char *)path);
	sort_struct_array_asc(arr, f_count);
	write_ls_only(arr, f_count);
	if (info->arg_count < 2)
		write(1, "\n", 1);
	free(arr);
}
