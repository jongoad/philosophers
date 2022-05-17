/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:21:34 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 14:30:34 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_data	*dat;
	char	*errmsg;

	errmsg = NULL;
	if (argc < 5)
		return (err_msg_ret(ERR_ARGC, 1));
	dat = (t_data *)malloc(sizeof(t_data));
	if (validate_input(dat, argc, argv))
		errmsg = ERR_ARGV;
	else if (dat->num_philo == 1)
		single_philo(dat);
	else if (init_sim(dat))
		errmsg = SEM_ERR;
	else
	{
		launch_sim(dat);
		monitor_sim(dat);
	}
	cleanup(dat);
	if (errmsg)
		return (err_msg_ret(errmsg, 1));
	return (0);
}

/* Monitor simulation and kill all processed when one dies */
void	monitor_sim(t_data *dat)
{
	int	status;
	int	ret;

	status = 0;
	ret = 0;
	while (1)
	{
		ret = waitpid(-1, &status, 0);
		if ((status >> 8 > 0) || track_eaten(dat, ret))
		{
			kill_all(dat);
			break ;
		}
		if (ret < 0)
			break ;
	}
}

/* Track how many philos have eaten n times */
int	track_eaten(t_data *dat, int ret_pid)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
	{
		if (ret_pid == dat->pids_msg[i])
			dat->num_finished++;
		i++;
	}
	if (dat->num_finished == dat->num_philo)
	{
		printf("%10li : All philosophers have eaten %i times.\n",
			get_time(dat), dat->num_eat);
		return (1);
	}
	return (0);
}

/* Function to kill all processes */
void	kill_all(t_data *dat)
{
	int	i;

	i = 0;
	while (i < dat->num_philo)
	{
		kill(dat->pids[i], SIGTERM);
		kill(dat->pids_msg[i], SIGTERM);
		i++;
	}
}

/* Cleanup semaphores and free data struct before progrem termination */
void	cleanup(t_data *dat)
{
	if (dat->forks > 0)
	{
		sem_close(dat->forks);
		sem_unlink("/forks");
	}
	if (dat->eat_check > 0)
	{
		sem_close(dat->eat_check);
		sem_unlink("/eat_check");
	}
	if (dat->write > 0)
	{
		sem_close(dat->write);
		sem_unlink("/write");
	}
	free(dat);
}
