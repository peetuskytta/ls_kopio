/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 10:07:54 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/15 16:40:12 by pskytta          ###   ########.fr       */
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
	info->padding[3] = 0;
	info->nb_of_args = 0;
	info->file_count = 0;
	info->flag_count = 0;
	info->link_count = 0;
	info->arg_count = 0;
	info->arguments_on = 0;
//	info->list = NULL;
//	info->dir = NULL;
//	info->ent = NULL;
	ft_strclr(info->path);
}

											//DELETE LATER
void	useful(t_data *data)
{
	printf("\nflag l:	%d\n", data->f_long);
	printf("flag a:	%d\n", data->f_all);
	printf("flag r:	%d\n", data->f_reve);
	printf("flag R:	%d\n", data->f_recu);
	printf("flag t:	%d\n", data->f_time);
	printf("file count:	%d\n", data->file_count);
	printf("flag count:	%d\n", data->flag_count);
	printf("Arg count:	%d\n", data->arg_count);
	printf("Original argc:	%d\n", data->nb_of_args);
	printf("Args on:	%d\n\n", data->arguments_on);
}

int	main(int argc, char **argv)
{
	t_data	*info;

	info = ft_memalloc(sizeof(t_data));
	primary_checks(argv, argc, info);
	ls_driver(info, argv, ".");
	if (argc > 0)
		ft_putchar('\n');
	free(info);
	return (0);
}
