/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:10:03 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 12:34:19 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Special case for single philosopher */
void	single_philo(t_data *dat)
{
	set_start_time(dat);
	if (dat->num_eat == 0)
	{
		printf("%10li : Philosopher 1 is thinking\n", get_time(dat));
		printf("%10li : Philosopher 1 is has taken a fork\n", get_time(dat));
		printf("%10li : All philosphers have eaten %i times\n",
			get_time(dat), dat->num_eat);
	}
	else
	{
		printf("%10li : Philosopher 1 is thinking\n", get_time(dat));
		printf("%10li : Philosopher 1 is has taken a fork\n", get_time(dat));
		usleep(dat->time_die * 1000);
		printf("%10li : Philosopher 1 has died\n", get_time(dat));
	}
}

/* Simulation function to be run by each thread */
void	*philo(void *philos)
{
	t_philo	*philo;
	t_data	*dat;

	philo = (t_philo *)philos;
	dat = philo->dat;
	while (dat->sim_state)
	{
		eat(philo);
		if (!dat->sim_state)
			break ;
		write_log(dat, philo->id, SLEEP);
		sync_sleep(dat, dat->time_sleep);
		write_log(dat, philo->id, THINK);
	}
	return (NULL);
}

/* Control function for eating, fork access, and sleeping */
void	eat(t_philo *philo)
{
	t_data	*dat;

	dat = philo->dat;
	while (!philo->is_turn)
		check_queue(dat, philo);
	pthread_mutex_lock(&dat->lock.eat_check);
	write_log(dat, philo->id, EAT);
	philo->last_eaten = get_time(dat);
	pthread_mutex_unlock(&dat->lock.eat_check);
	sync_sleep(dat, dat->time_eat);
	(philo->n_eaten)++;
	philo->is_turn = false;
	pthread_mutex_unlock(&dat->lock.forks[philo->left_fork]);
	pthread_mutex_unlock(&dat->lock.forks[philo->right_fork]);
}

/* Check queue position */
void	check_queue(t_data *dat, t_philo *philo)
{
	pthread_mutex_lock(&dat->lock.queue_check);
	if (dat->queue[0] == philo->id)
	{
		philo->is_turn = true;
		shift_queue(dat);
		pthread_mutex_lock(&dat->lock.forks[philo->left_fork]);
		write_log(dat, philo->id, FORK);
		pthread_mutex_lock(&dat->lock.forks[philo->right_fork]);
		write_log(dat, philo->id, FORK);
	}
	pthread_mutex_unlock(&dat->lock.queue_check);
}

/* Launch the simulation by calling all threads */
void	launch_sim(t_data *dat)
{
	int	i;

	i = 0;
	set_start_time(dat);
	while (i < dat->num_philo)
	{
		pthread_create(&dat->philo[i].thread_id, NULL, &philo, &dat->philo[i]);
		i++;
	}
}
