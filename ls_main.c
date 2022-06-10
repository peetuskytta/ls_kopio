/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:07:54 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/10 14:41:27 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_variables(t_data *info)
{
	info->f_all = 0;
	info->f_long = 0;
	info->f_reve = 0;
	info->f_recu = 0;
	info->f_time = 0;
	info->padding[0] = 0;
	info->padding[1] = 0;
	info->padding[2] = 0;
	info->file_count = 0;
	info->flag_count = 0;
	info->link_count = 0;
	info->arg_count = 0;
	ft_strclr(info->path);
}

void	useful(t_data *data)
{
	printf("\nflag l: %d\n", data->f_long);
	printf("flag a: %d\n", data->f_all);
	printf("flag r: %d\n", data->f_reve);
	printf("flag R: %d\n", data->f_recu);
	printf("flag t: %d\n", data->f_time);
	printf("file count: %d\n", data->file_count);
	printf("flag count: %d\n", data->flag_count);
	printf("Arg count: %d\n\n", data->arg_count);
}

int	main(int argc, char **argv)
{
	t_data	*info;

	info = ft_memalloc(sizeof(t_data));
	primary_checks(argv, argc, info);
	useful(info); //DELETE
	ft_putendl("non-flag ARGUMENTS:"); //DELETE
	print_double(info->list); //DELETE
	ft_putendl(""); //DELETE
	ls_driver(info);
	ft_free_array(info->arg_count, info->list);
	free(info);
	return (0);
}
