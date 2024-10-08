/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:37:03 by sarif             #+#    #+#             */
/*   Updated: 2024/10/08 20:37:28 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sleepodd(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->eating_time / 2);
}

static int	breaksim(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->lock.mtx);
	pthread_mutex_lock(&philo->protect.mtx);
	if (philo->data->dead_flag
		|| (philo->meals && philo->meals == philo->data->meals))
		result = 1;
	else
		result = 0;
	pthread_mutex_unlock(&philo->data->lock.mtx);
	pthread_mutex_unlock(&philo->protect.mtx);
	return (result);
}

bool	get_bool(t_data *data, bool *src)
{
	bool	store;

	pthread_mutex_lock(&data->lock.mtx);
	store = *src;
	pthread_mutex_unlock(&data->lock.mtx);
	return (store);
}

void	*simulation(t_philo *philo)
{
	sleepodd(philo);
	while (1)
	{
		if (breaksim(philo))
			return (NULL);
		eating_time(philo);
		if (breaksim(philo))
			return (NULL);
		if (philo->data->philo_num > 1)
		{
			sleeping_time(philo);
			if (breaksim(philo))
				return (NULL);
			ft_printf(4, philo->data, philo->id);
		}
		else
			ft_usleep(philo->data->dying_time + 2);
	}
	return (NULL);
}
