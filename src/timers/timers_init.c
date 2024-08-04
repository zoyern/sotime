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
#include <solibft/sostdlib.h>
#include <solibft/sostring.h>

t_sotimer	*timer_list_add(t_soloop *loop, int start, long millis)
{
	t_sotimer	*timer;

	if (!loop)
		timer = somalloc(NULL, sizeof(t_sotimer));
	else
		timer = somalloc(loop->solib, sizeof(t_sotimer));
	timer->start = start;
	timer->millis = 0;
	timer->start_millis = 0;
	timer->working = 0;
	timer->finish = 0;
	timer->time = millis;
	if (!loop)
		return (timer);
	timer->next = loop->timers->first;
	loop->timers->first = timer;
	return (timer);
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

t_sotimer	**create_timers(t_solib *solib, t_soloop *loop, char **strs)
{
	t_sotimer	**timers;
	int			i;	

	i = 0;
	while (strs[i])
		i++;
	timers = solib->malloc(solib, sizeof(t_sotimer *) * (i + 1));
	i = 0;
	while (strs[i])
	{
		timers[i] = loop->timers->new(loop, 0, ft_atoi(strs[i]));
		i++;
	}
	timers[i] = NULL;
	return (timers);
}
