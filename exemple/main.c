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
#include <solibft/sostring.h>

int	my_update(t_soloop *loop, t_data *data)
{
	if (data->dying->finish)
	{
		loop->print("%d -- die\n", loop->millis);
		loop->stop = 1;
		return (0);
	}
	if (!loop->millis)
	{
		data->dying->start = 1;
		data->eat->start = loop->print("%d -- eat\n", loop->millis);
	}
	if (data->eat->finish)
		data->timers[0]->start = loop->print("%d -- think\n", loop->millis);
	if (data->timers[0]->finish)
		data->timers[1]->start = loop->print("%d -- drink\n", loop->millis);
	if (data->timers[1]->finish)
		data->sleep->start = loop->print("%d -- sleep\n", loop->millis);
	if (data->sleep->finish)
	{
		loop->timers->reset(loop, data->dying, 1);
		data->eat->start = loop->print("%d -- eat\n", loop->millis);
	}
	return (0);
}

int	core(t_solib *solib)
{
	t_data		*data;
	t_soloop	*loop;

	loop = solib->time->loop(solib);
	data = solib->malloc(solib, sizeof(t_data));
	data->eat = loop->timers->new(loop, 0, 200);
	data->sleep = loop->timers->new(loop, 0, 200);
	data->timers = loop->create_timers(solib, loop,
			ft_split(solib, "200,200", ','));
	data->dying = loop->timers->new(loop, 0, 1600);
	solib->time->start(loop, 1, data, my_update);
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
