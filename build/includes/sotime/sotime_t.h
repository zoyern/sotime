/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_t.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almounib <almounib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:27:45 by marvin            #+#    #+#             */
/*   Updated: 2024/05/20 17:45:02 by almounib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOTIME_T_H
# define SOTIME_T_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sotypes.h>
# include <solibft.h>

typedef struct s_sotime			t_sotime;
typedef struct s_sotimer		t_sotimer;
typedef struct s_sotimers_list	t_sotimers_list;
typedef struct s_soloop			t_soloop;

typedef struct s_sotimer
{
	int			start;
	int			working;
	int			finish;
	long		start_millis;
	long		millis;
	long		time;
	t_sotimer	*next;
}	t_sotimer;

typedef struct s_sotimers_list
{
	t_sotimer	*first;
	t_sotimer	*(*new)(t_soloop *loop, int start, long millis);
	void		(*reset)(t_soloop *loop, t_sotimer *timer, int start);
	void		(*clear)(t_soloop *loop);
}	t_sotimers_list;

typedef struct s_soloop
{
	int				stop;
	t_solib			*solib;
	t_sotimers_list	*timers;
	long			starting_time;
	long			current;
	long			last_time;
	long			millis_update;
	long			millis;
	long			(*get_millis)();
	t_sotimer		**(*create_timers)(t_solib *solib, t_soloop *loop,
			char **strs);
	void			(*update)(t_soloop *loop, int passed);
	int				(*print)(const char *str, ...);
}	t_soloop;

typedef struct s_sotime
{
	t_soloop		*(*loop)(t_solib *solib);
	int				(*start)(t_soloop *loop, long millis,
			void *data, int (*callback)());
	int				(*close)(t_solib *solib, int state);
}	t_sotime;

#endif