/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:22:38 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 13:41:02 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/* Convert a value held in a string to an int */
int	ft_atoi(const char *str)
{
	long long	num;
	long long	sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
		if ((num * sign) > INT_MAX)
			return (-1);
		if ((num * sign) < INT_MIN)
			return (0);
	}
	return (num * sign);
}

/* Mutex protected write function */
void	write_log(t_data *dat, int id, char *str, int i)
{
	sem_wait(dat->write);
	printf("%10li : Philospher %i %s\n", get_time(dat), id + 1, str);
	if (i)
		sem_post(dat->write);
}

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

/* Print error message and return value */
int	err_msg_ret(char *msg, int ret)
{
	putstr_fd(msg, 2);
	putstr_fd("\n", 2);
	return (ret);
}
