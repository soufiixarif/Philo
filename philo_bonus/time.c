/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:35 by sarif             #+#    #+#             */
/*   Updated: 2024/09/29 22:22:27 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(long milliseconds)
{
	long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < milliseconds)
		usleep(150);
	return (0);
}

int	is_full(t_philo philo, t_data *data)
{
	if (data->meals != -1 && philo.meals >= data->meals)
		return (1);
	return (0);
}

void	ft_unlock(t_philo *philo, t_data *data)
{
	(void)data;
	sem_post(philo->philo_sem);
	sem_close(philo->philo_sem);
	sem_unlink(philo->philo_name);
	free(philo->philo_name);
}
