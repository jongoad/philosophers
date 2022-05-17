/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:58:57 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 14:46:03 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char	*argv[])
{
	t_data	*dat;

	if (argc < 5)
		return (err_msg_ret(ERR_ARGC, 1));
	dat = get_data();
	if (validate_input(dat, argc, argv))
	{
		free(dat);
		return (err_msg_ret(ERR_ARGV, 1));
	}
	if (dat->num_philo == 1)
	{
		single_philo(dat);
		free(dat);
	}
	else
	{
		init_sim(dat);
		launch_sim(dat);
		monitor_sim(dat);
		cleanup(dat);
	}
}

/* Monitor simulation to check for philo death, or all eaten n times */
void	monitor_sim(t_data *dat)
{
	while (dat->sim_state)
	{
		if (check_death(dat))
			return ;
		if (dat->num_eat != -1 && check_eaten(dat))
			return ;
		usleep(100);
	}
}

/* Check if any philosophers have died */
int	check_death(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
	{
		if ((get_time(dat) - dat->philo[i].last_eaten) >= dat->time_die)
		{
			dat->sim_state = false;
			printf("%10li : Philosopher %i has died\n", get_time(dat), i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

/* Check if all philosophers have finished eating */
int	check_eaten(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
	{
		pthread_mutex_lock(&(dat->lock.eat_check));
		if (dat->philo[i].n_eaten < dat->num_eat)
		{
			pthread_mutex_unlock(&(dat->lock.eat_check));
			break ;
		}
		pthread_mutex_unlock(&(dat->lock.eat_check));
		i++;
	}
	if (i == dat->num_philo)
	{
		dat->sim_state = false;
		printf("%10li : All philosophers have eaten %i times\n",
			get_time(dat), dat->num_eat);
		return (1);
	}
	return (0);
}

/* Free all allocated memory, join threads, and destroy mutexes */
void	cleanup(t_data *dat)
{
	int	i;

	i = 0;
	dat->sim_state = false;
	while (i < dat->num_philo)
	{
		pthread_join(dat->philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < dat->num_philo)
	{
		pthread_mutex_destroy(&dat->lock.forks[i]);
		i++;
	}
	pthread_mutex_destroy(&dat->lock.eat_check);
	pthread_mutex_destroy(&dat->lock.write);
	pthread_mutex_destroy(&dat->lock.queue_check);
	free(dat->queue);
	free(dat);
}
