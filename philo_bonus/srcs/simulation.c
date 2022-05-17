/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:22:16 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 13:42:10 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* Handle single philosopher */
void	single_philo(t_data *dat)
{
	set_start_time(dat);
	printf("%10li : Philosopher 1 is thinking\n", get_time(dat));
	printf("%10li : Philosopher 1 has taken a fork\n", get_time(dat));
	usleep(dat->time_die * 1000);
	printf("%10li : Philosopher 1 has died\n", get_time(dat));
}

/* Child process philo function */
void	philo(void *data, int i)
{
	t_data	*dat;

	dat = *(t_data **)data;
	dat->id = i;
	dat->last_eaten = get_time(dat);
	pthread_create(&(dat->thread_id), NULL, &check_death, dat);
	while (dat->is_alive)
	{
		eat(dat);
		if (dat->n_eaten >= dat->num_eat && dat->num_eat
			!= -1 && !dat->msg_sent)
		{
			dat->msg_sent = true;
			kill(dat->pids_msg[dat->id], SIGTERM);
		}
		write_log(dat, dat->id, SLEEP, ALIVE);
		sync_sleep(dat, dat->time_sleep);
		write_log(dat, dat->id, THINK, ALIVE);
	}
	pthread_join(dat->thread_id, NULL);
	free(dat);
	exit(0);
}

/* Control function for eating, sleeping, and fork access */
void	eat(t_data *dat)
{
	sem_wait(dat->eat_check);
	sem_wait(dat->forks);
	write_log(dat, dat->id, FORK, ALIVE);
	sem_wait(dat->forks);
	write_log(dat, dat->id, FORK, ALIVE);
	write_log(dat, dat->id, EAT, ALIVE);
	dat->last_eaten = get_time(dat);
	sem_post(dat->eat_check);
	sync_sleep(dat, dat->time_eat);
	(dat->n_eaten)++;
	sem_post(dat->forks);
	sem_post(dat->forks);
}

/* Check if philosopher has died */
void	*check_death(void *data)
{
	t_data	*dat;

	dat = (t_data *)data;
	while (1)
	{
		sem_wait(dat->eat_check);
		if ((get_time(dat) - dat->last_eaten) >= dat->time_die)
		{
			write_log(dat, dat->id, DIED, DEAD);
			dat->is_alive = false;
			free(dat);
			exit(1);
		}
		sem_post(dat->eat_check);
		usleep(100);
		if (dat->n_eaten >= dat->num_eat && dat->num_eat != -1)
			break ;
	}
	return (NULL);
}

/* Sacrificial process function to send eaten data to main process */
void	philo_messenger(void)
{
	while (1)
		usleep(1000 * 1000);
}
