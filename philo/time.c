/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:37:05 by sarif             #+#    #+#             */
/*   Updated: 2024/10/08 20:26:31 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(100);
	return (0);
}

int	ft_mutex_init(t_mtx *mutex)
{
	if (pthread_mutex_init(&mutex->mtx, NULL) != 0)
		return (mutex->init = false, 0);
	mutex->init = true;
	return (1);
}

void	init_to_false(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		data->forks[i].init = false;
		data->philos[i].protect.init = false;
	}
}
