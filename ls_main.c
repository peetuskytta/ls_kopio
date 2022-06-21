/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:02:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 11:53:29 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Function to handle the simplest cases and redirect to initial cases.
*/
static void	ls_arg_flag_driver(t_data *info, char **str)
{
	if (info->arg_count > 0)
		store_and_process_arguments(&str[info->flag_count + 1], info);
	else if (info->arg_count == 0 && info->flag_count > 0)
		ls_driver(info, ".");
	else
	{
		no_flags(info, ".");
		write(1, "\n", 1);
	}
}

int	main(int argc, char **argv)
{
	t_data	*info;

	info = (t_data *)ft_memalloc(sizeof(t_data));
	primary_checks(argv, argc, info);
	ls_arg_flag_driver(info, argv);
	free(info);
	system("leaks ft_ls");
	return (0);
}
