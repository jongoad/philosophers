/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:46:21 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 12:47:05 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Set start time for simulation */
void	set_start_time(t_data *dat)
{
	gettimeofday(&dat->time, NULL);
	dat->ts.sec = dat->time.tv_sec;
	dat->ts.usec = dat->time.tv_usec;
}

/* Get current elapsed time since simulation start */
time_t	get_time(t_data *dat)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (((t.tv_sec - dat->ts.sec) * 1000)
		+ ((t.tv_usec - dat->ts.usec) / 1000));
}

/* Smart sleep function to keep time synchronized */
void	sync_sleep(t_data *dat, time_t time)
{
	time_t	t;

	t = get_time(dat);
	while (dat->sim_state)
	{
		if (get_time(dat) - t >= time)
			break ;
		usleep(50);
	}
}
