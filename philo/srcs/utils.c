/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgoad <jgoad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:59:16 by jgoad             #+#    #+#             */
/*   Updated: 2022/05/17 12:49:26 by jgoad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* Convert a value from a string to and integer */
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

/* Move first in queue to the end of queue */
void	shift_queue(t_data *dat)
{
	int	i;
	int	tmp1;
	int	tmp2;

	i = dat->num_philo - 1;
	tmp1 = dat->queue[0];
	while (i >= 0)
	{
		tmp2 = dat->queue[i];
		dat->queue[i] = tmp1;
		tmp1 = tmp2;
		i--;
	}
}

/* Singleton function to get data struct */
t_data	*get_data(void)
{
	static t_data	*dat;

	if (!dat)
		dat = malloc(sizeof(t_data));
	return (dat);
}
