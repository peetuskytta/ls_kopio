/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:02:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/17 18:42:41 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	ls_arg_flag_driver(t_data *info, char **str)
{
	if (info->arg_count > 0)
		store_and_process_arguments(&str[info->flag_count + 1], info);
	else if (info->arg_count == 0)
		ls_driver(info, ".");
	else
		no_flags(info, ".");
}

int	main(int argc, char **argv)
{
	t_data	*info;

	info = (t_data *)malloc(sizeof(t_data));
	primary_checks(argv, argc, info);
	ls_arg_flag_driver(info, argv);
	free(info);
	return (0);
}
