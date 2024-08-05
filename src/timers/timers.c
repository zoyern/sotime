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
#include <sotypes/somemory.h>

void	timer_reset(t_soloop *loop, t_sotimer *timer)
{
	timer->start_millis = loop->millis + (loop->millis - loop->last_time);
	timer->millis = 0;
	timer->working = 1;
	timer->start = 0;
}

void	timer_list_clear(t_soloop *loop)
{
	t_sotimer	*box;
	t_sotimer	*tmp;

	if (!loop || !loop->timers)
		return ;
	box = loop->timers->first;
	while (box)
	{
		tmp = box->next;
		sofree(loop->solib, box);
		box = tmp;
	}
	sofree(loop->solib, loop->timers);
	loop->timers = NULL;
}

void	sotime_update_timer(t_soloop *loop, t_sotimer *timer, int passed, int deleyed)
{
	if (!timer)
		return ;
	(void)deleyed;
	if (timer->start)
	{
		timer->start_millis = loop->millis;
		timer->millis = 0;
		timer->working = 1;
		timer->start = 0;
	}
	if (timer->finish && passed)
		timer->finish = 0;
	if (timer->working && !timer->start && timer->millis >= timer->time)
	{
		timer->working = 0;
		timer->finish = 1;
		timer->millis = 0;
	}
	if (timer->working)
		timer->millis = loop->millis - timer->start_millis;
}
