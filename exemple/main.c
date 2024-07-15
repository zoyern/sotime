/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:00:14 by marvin            #+#    #+#             */
/*   Updated: 2024/05/16 14:35:26 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exemple.h"

int	my_update(t_solib *solib, t_data *data, long time)
{
	if (!time)
	{
		data->dying->start = 1;
		data->eat->start = solib->print("%d -- eat\n", time);
	}
	if (data->eat->finish)
		data->think->start = solib->print("%d -- think\n", time);
	if (data->think->finish)
		data->sleep->start = solib->print("%d -- sleep\n", time);
	if (data->sleep->finish)
		data->eat->start = solib->print("%d -- eat\n", time);
	if (data->dying->finish)
		solib->time->stop = 1;
	return (0);
}

int	core(t_solib *solib)
{
	t_data	*data;

	data = solib->malloc(solib, sizeof(t_data));
	data->eat = solib->time->timers->new(solib, 0, 500);
	data->think = solib->time->timers->new(solib, 0, 500);
	data->sleep = solib->time->timers->new(solib, 0, 500);
	data->dying = solib->time->timers->new(solib, 0, 5000);
	solib->time->loop(solib, 1, data, my_update);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_solib	*solib;

	solib = sonew_libft(sonew_types(argc, argv, envp));
	if (!solib)
		return (solib->close(solib, EXIT_FAILURE));
	solib = sonew_time(solib);
	if (!solib->time)
		return (solib->close(solib, EXIT_FAILURE));
	core(solib);
	return (solib->close(solib, EXIT_SUCCESS));
}
