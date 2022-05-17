/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:36:32 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 12:47:16 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Check input variables for validity */
int	validate_input(t_data *dat, int argc, char **argv)
{
	dat->num_philo = ft_atoi(argv[1]);
	dat->time_die = ft_atoi(argv[2]);
	dat->time_eat = ft_atoi(argv[3]);
	dat->time_sleep = ft_atoi(argv[4]);
	if (dat->num_philo < 1 || dat->time_die < 0
		|| dat->time_eat < 0 || dat->time_sleep < 0)
		return (1);
	if (argc > 5)
	{
		dat->num_eat = ft_atoi(argv[5]);
		if (dat->num_eat < 0)
			return (1);
	}
	else
		dat->num_eat = -1;
	return (0);
}

/* Initialize simulation variables */
void	init_sim(t_data *dat)
{
	dat->sim_state = true;
	init_philos(dat);
	init_queue(dat);
	init_forks(dat);
	pthread_mutex_init(&dat->lock.eat_check, 0);
	pthread_mutex_init(&dat->lock.write, 0);
}

/* Initialize variables for individual philo structs */
void	init_philos(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
	{
		dat->philo[i].id = i;
		dat->philo[i].left_fork = i;
		if (i == dat->num_philo - 1)
			dat->philo[i].right_fork = 0;
		else
			dat->philo[i].right_fork = i + 1;
		dat->philo[i].n_eaten = 0;
		dat->philo[i].last_eaten = 0;
		dat->philo[i].dat = dat;
		dat->philo[i].is_turn = false;
		i++;
	}
}

/* Initialize the queue and queue_check lock */
void	init_queue(t_data *dat)
{
	int	i;
	int	set_ctl;

	i = 0;
	set_ctl = 1;
	pthread_mutex_init(&dat->lock.queue_check, 0);
	dat->queue = (int *)malloc(sizeof(int) * dat->num_philo);
	while (i < dat->num_philo / 2)
	{
		dat->queue[i] = i + set_ctl;
		set_ctl++;
		i++;
	}
	set_ctl = 0;
	while (i < dat->num_philo)
	{
		dat->queue[i] = set_ctl * 2;
		set_ctl++;
		i++;
	}
}

/* Initialize mutex locks for forks */
void	init_forks(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
	{
		pthread_mutex_init(&dat->lock.forks[i], 0);
		i++;
	}
}
