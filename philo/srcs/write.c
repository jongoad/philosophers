/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:31:19 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 12:36:03 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Write a char to the specified FD */
void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* Write a string to the specified FD */
void	putstr_fd(char *s, int fd)
{
	while (s != NULL && *s)
	{
		putchar_fd(*s, fd);
		s++;
	}
}

/* Mutex protected write function */
void	write_log(t_data *dat, int id, char *str)
{
	pthread_mutex_lock(&dat->lock.write);
	if (dat->sim_state)
		printf("%10li : Philospher %i %s\n", get_time(dat), id + 1, str);
	pthread_mutex_unlock(&dat->lock.write);
}

/* Print error message and return value */
int	err_msg_ret(char *msg, int ret)
{
	putstr_fd(msg, 2);
	putstr_fd("\n", 2);
	return (ret);
}
