/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sotime/all.h>
#include <stdio.h>

void	updating_time(t_soloop *loop, int passed)
{
	t_sotimer	*box;

	if (!loop || !loop->solib || loop->stop)
		return ;
	loop->last_time = loop->millis;
	loop->current = sotime_get_millis();
	loop->millis = loop->current - loop->starting_time;
	if (loop->millis - loop->last_time > loop->millis_update)
	{
		loop->starting_time += (loop->millis - loop->last_time);
		loop->millis = loop->current - loop->starting_time;
	}
	box = loop->timers->first;
	while (box->next)
	{
		sotime_update_timer(loop, box, passed);
		box = box->next;
	}
}

void	sotime_restart_loop(t_soloop *loop, long millis)
{
	loop->stop = 0;
	loop->starting_time = sotime_get_millis();
	loop->current = loop->starting_time;
	loop->millis = 0;
	loop->millis_update = millis;
	loop->last_time = 0;
}

int	sotime_loop(t_soloop *loop, long millis, void *data, int (*callback)())
{
	long	current;
	long	start;
	int		passed;

	if (!loop || !loop->solib)
		return (1);
	sotime_restart_loop(loop, millis);
	start = -millis;
	current = millis;
	passed = 0;
	while (!loop->stop)
	{
		passed = 0;
		if (current >= millis)
		{
			passed = 1;
			if (callback)
				if (callback(loop, data, loop->millis))
					return (1);
			start = loop->millis;
		}
		current = loop->millis - start;
		updating_time(loop, passed);
	}
	return (0);
}

long	sotime_get_millis(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

t_sotimer	sotime_timer_init(int start)
{
	t_sotimer	timer;

	timer.start = start;
	timer.millis = 0;
	timer.start_millis = 0;
	timer.working = 0;
	timer.finish = 0;
	return (timer);
}
