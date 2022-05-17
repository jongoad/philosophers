/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:22:27 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 13:40:29 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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
int	init_sim(t_data *dat)
{
	sem_unlink("/forks");
	sem_unlink("/eat_check");
	sem_unlink("/write");
	dat->forks = sem_open("/forks", O_CREAT, S_IRWXU, dat->num_philo);
	dat->eat_check = sem_open("/eat_check", O_CREAT, S_IRWXU, 1);
	dat->write = sem_open("/write", O_CREAT, S_IRWXU, 1);
	dat->n_eaten = 0;
	dat->last_eaten = 0;
	dat->is_alive = true;
	dat->num_finished = 0;
	dat->msg_sent = false;
	if (dat->forks <= 0 || dat->eat_check <= 0 || dat->write <= 0)
		return (1);
	return (0);
}

/* Launch simulation processes */
void	launch_sim(t_data *dat)
{
	int	i;

	set_start_time(dat);
	if (dat->num_eat == 0)
	{
		printf("%10li : All philosophers have eaten %i times.\n",
			get_time(dat), dat->num_eat);
		return ;
	}
	i = -1;
	while (++i < dat->num_philo)
	{
		dat->pids_msg[i] = fork();
		if (dat->pids_msg[i] == 0)
			philo_messenger();
	}
	i = -1;
	while (++i < dat->num_philo)
	{
		dat->pids[i] = fork();
		if (dat->pids[i] == 0)
			philo(&dat, i);
		usleep(100);
	}
}
