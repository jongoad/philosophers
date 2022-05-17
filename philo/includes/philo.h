/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:57:52 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 12:38:56 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* System includes */
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

/* Error string defines */
# define ERR_ARGC "Invalid argument count."
# define ERR_ARGV "Invalid argument values."

/* Log string defines */
# define THINK "is thinking"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define DIED "has died"
# define FORK "has picked up a fork"

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

/* Mutex stuct */
typedef struct s_locks
{
	pthread_mutex_t	write;
	pthread_mutex_t	forks[300];
	pthread_mutex_t	eat_check;
	pthread_mutex_t	queue_check;
}	t_locks;

/* Individual philosopher struct */
typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			n_eaten;
	time_t		last_eaten;
	t_data		*dat;
	pthread_t	thread_id;
	bool		is_turn;
}	t_philo;

/* Main data struct */
struct s_data
{
	int				num_philo;
	time_t			time_eat;
	time_t			time_die;
	time_t			time_sleep;
	int				num_eat;
	t_philo			philo[300];
	t_locks			lock;
	int				*queue;
	bool			sim_state;
	struct timeval	time;
	t_time			ts;
};

/*
------- Function Prototypes -------
*/

/* Simulation functions */
void	single_philo(t_data *dat);
void	*philo(void *philos);
void	eat(t_philo *philo);
void	launch_sim(t_data *dat);
void	monitor_sim(t_data *dat);
int		check_death(t_data *dat);
int		check_eaten(t_data *dat);
void	check_queue(t_data *dat, t_philo *philo);
void	shift_queue(t_data *dat);
void	cleanup(t_data *dat);

/* Initialization functions */
int		validate_input(t_data *dat, int argc, char **argv);
void	init_sim(t_data *dat);
void	init_philos(t_data *dat);
void	init_queue(t_data *dat);
void	init_forks(t_data *dat);

/* Utility functions */
t_data	*get_data(void);
int		err_msg_ret(char *msg, int ret);
void	write_log(t_data *dat, int id, char *str);
void	putstr_fd(char *s, int fd);
void	putchar_fd(char c, int fd);
int		ft_atoi(const char *str);

/* Time functions */
void	set_start_time(t_data *dat);
time_t	get_time(t_data *dat);
void	sync_sleep(t_data *dat, time_t time);
#endif