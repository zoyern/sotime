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
#include <stdio.h>

t_sotimer	*timer_list_add(t_soloop *loop, int start, long millis)
{
	t_sotimer	*timer;

	timer = somalloc(loop->solib, sizeof(t_sotimer));
	timer->start = start;
	timer->millis = 0;
	timer->start_millis = 0;
	timer->working = 0;
	timer->finish = 0;
	timer->time = millis;
	timer->next = loop->timers->first;
	loop->timers->first = timer;
	return (timer);
}

void	timer_reset(t_soloop *loop, t_sotimer *timer, int start)
{
	(void)loop;
	timer->start_millis = 0;
	timer->millis = 0;
	timer->working = 0;
	timer->start = start;
	timer->finish = 0;
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

t_sotimers_list	*sonew_timers_list(t_solib *solib)
{
	t_sotimers_list	*list;

	list = somalloc(solib, sizeof(t_sotimers_list));
	list->first = somalloc(solib, sizeof(t_sotimer));
	list->first->next = NULL;
	list->new = timer_list_add;
	list->reset = timer_reset;
	list->clear = timer_list_clear;
	return (list);
}

void	sotime_update_timer(t_soloop *loop, t_sotimer *timer, int passed)
{
	if (!timer)
		return ;
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
