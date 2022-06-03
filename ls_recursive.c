/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_recursive.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:23:34 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/03 12:58:08 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_recursive(t_data *info)
{
	t_file	*arr;

	arr = read_dir_stream(info, 0);
	sort_driver(arr, info);
	print_short(arr, info);
	free(arr);
}

void	print_short(t_file *arr, t_data *info)
{
	int	i;

	i = 0;
	while (i < info->file_count)
	{
		ft_putendl(arr[i].name);
		i++;
	}
}
