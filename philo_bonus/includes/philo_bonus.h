/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:21:14 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 13:43:02 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/* System includes */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h> 
# include <signal.h>
# include <pthread.h>

/* Error string defines */
# define ERR_ARGC "Invalid argument count."
# define ERR_ARGV "Invalid argument values."
# define SEM_ERR "Unable to open semaphore"

/* Log string defines */
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "has died"
# define FORK "has picked up a fork"

enum e_state
{
	DEAD = 0,
	ALIVE = 1
};

/*
------- Struct Definitions -------
*/

typedef struct s_data	t_data;

/* Timer struct */
typedef struct s_time
{
	suseconds_t		usec;
	time_t			sec;
	time_t			msec;
}	t_time;

/* Main data struct */
struct s_data
{
	int				num_philo;
	time_t			time_eat;
	time_t			time_die;
	time_t			time_sleep;
	int				num_eat;
	time_t			last_eaten;
	int				n_eaten;
	bool			is_alive;
	int				id;
	pthread_t		thread_id;
	bool			msg_sent;
	sem_t			*forks;
	sem_t			*eat_check;
	sem_t			*write;
	pid_t			pids[300];
	int				num_finished;
	pid_t			pids_msg[300];
	struct timeval	time;
	t_time			ts;
};

/*
------- Function Prototypes -------
*/

/* Simulation functions */
void	single_philo(t_data *dat);
void	eat(t_data *dat);
void	philo(void *data, int i);
void	check_meals(t_data *dat, int id);
void	send_eaten(t_data *dat);
void	monitor_sim(t_data *dat);
void	*check_death(void *data);
int		track_eaten(t_data *dat, int ret_pid);
void	philo_messenger(void);
void	kill_all(t_data *dat);
void	cleanup(t_data *dat);

/* Initialization functions */
int		init_sim(t_data *dat);
int		validate_input(t_data *dat, int argc, char **argv);
void	launch_sim(t_data *dat);

/* Utility functions */
int		ft_atoi(const char *str);
void	write_log(t_data *dat, int id, char *str, int i);
void	putchar_fd(char c, int fd);
void	putstr_fd(char *s, int fd);
int		err_msg_ret(char *msg, int ret);

/* Time functions */
void	set_start_time(t_data *dat);
time_t	get_time(t_data *dat);
void	sync_sleep(t_data *dat, time_t time);

#endif