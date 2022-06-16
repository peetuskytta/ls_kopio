/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_driver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:07:03 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/16 16:15:57 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_arg_flag_driver(t_data *info, char **str)
{
	if (info->arg_count > 0)
	{
		//ft_putendl("\n-------------WITH ARGUMENTS");
		store_and_process_arguments(&str[info->flag_count + 1], info);
		//ft_putendl("\n-------------END ARGUMENTS");
		return ;

	}
	else if (info->arg_count == 0)
	{
		//ft_putendl("\n-------------DRIVER");
		ls_driver(info, ".");
	}
	else
	{
		no_flags(info, ".");
		//ft_putendl("\n-------------NO_FLAGS");
	}
}

void	sort_driver(t_file *arr, t_data *info, int f_count)
{
	sort_struct_array_asc(arr, f_count);
	if (info->f_time == 1)
		sort_struct_time(arr, f_count);
	if (info->f_reve == 1)
		sort_struct_reverse(arr, f_count - 1);
	if (info->arguments_on == 0)
		print_driver(arr, info, f_count);
}
//save_padding(arr, info, 0, f_count);

void	print_driver(t_file *arr, t_data *info, int f_count)
{
	if (info->f_long == 1)
	{
		write_long_output(arr, info, f_count, 0);
	}
	else
		print_short(arr, f_count);
	write(1, "\n", 1);
}
