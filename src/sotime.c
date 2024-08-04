/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:31:29 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 16:53:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sotime/all.h>
#include <sotypes/somemory.h>
#include <sotypes/soprintf.h>

int	sotime_close(t_solib *solib, int status)
{
	if (!solib)
	{
		free(solib->time);
		if (status)
			exit(status);
		return (status);
	}
	if (status)
		solib->close(solib, status);
	return (status);
}

t_soloop	*soloop_init(t_solib *solib)
{
	t_soloop	*loop;

	loop = (t_soloop *)somalloc(solib, sizeof(t_soloop));
	loop->solib = solib;
	loop->starting_time = 0;
	loop->millis = 0;
	loop->stop = 0;
	loop->timers = sonew_timers_list(solib);
	loop->current = 0;
	loop->get_millis = sotime_get_millis;
	loop->update = updating_time;
	loop->print = soprintf;
	return (loop);
}

void	sotime_init(t_sotime *sotime)
{
	sotime->loop = soloop_init;
	sotime->start = sotime_loop;
	sotime->close = sotime_close;
}

t_solib	*sonew_time(t_solib *solib)
{
	t_sotime	*sotime;

	if (!solib)
		return (NULL);
	if (!solib->libft)
		solib = sonew_libft(solib);
	if (!solib->libft)
		solib->close(solib, EXIT_FAILURE);
	sotime = (t_sotime *)somalloc(solib, sizeof(t_sotime));
	sotime_init(sotime);
	solib->time = sotime;
	return (solib);
}
