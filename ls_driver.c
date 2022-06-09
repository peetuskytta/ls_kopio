/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_driver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:07:03 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/09 15:17:49 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_driver(t_data *info)
{
	if (info->flag_count == 0)
		ls_only(info, 0);
	else if (info->f_recu == 1)
		ls_recursive(info, ".", 0);
	else
		ls_with_flags(info, ".");
}

void	sort_driver(t_file *arr, t_data *info, int f_count)
{
	sort_struct_array_asc(arr, f_count);
	if (info->f_time == 1)
		sort_struct_time(arr, f_count);
	if (info->f_reve == 1)
		sort_struct_reverse(arr, f_count - 1);
	save_padding(arr, info, 0, f_count);
	print_driver(arr, info, f_count);
}

void	print_driver(t_file *arr, t_data *info, int f_count)
{
	if (info->f_long == 1)
	{
		write_long_output(arr, info, f_count, 0);
	}
	else
		print_short(arr, f_count);
}
