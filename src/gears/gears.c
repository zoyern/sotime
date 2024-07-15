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

void	updating_time(t_solib *solib, int passed)
{
	t_sotimer	*box;

	if (!solib || !solib->time || solib->time->stop)
		return ;
	solib->time->current = sotime_get_millis();
	solib->time->millis = solib->time->current - solib->time->starting_time;
	box = solib->time->timers->first;
	while (box->next)
	{
		sotime_update_timer(solib, box, passed);
		box = box->next;
	}
}

void	sotime_restart_loop(t_solib *solib)
{
	solib->time->stop = 0;
	solib->time->starting_time = sotime_get_millis();
}

int	sotime_loop(t_solib *solib, long millis, void *data, int (*callback)())
{
	long	current;
	long	start;
	int		passed;

	if (!solib || !solib->time)
		return (1);
	sotime_restart_loop(solib);
	start = -millis;
	current = millis;
	passed = 0;
	while (!solib->time->stop)
	{
		passed = 0;
		if (current >= millis)
		{
			passed = 1;
			if (callback)
				if (callback(solib, data, solib->time->millis))
					return (1);
			start = solib->time->millis;
		}
		current = solib->time->millis - start;
		updating_time(solib, passed);
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
