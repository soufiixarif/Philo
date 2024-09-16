/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:37:03 by sarif             #+#    #+#             */
/*   Updated: 2024/09/12 20:06:22 by sarif            ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead_flag
		|| (philo->meals && philo->meals == philo->data->meals))
		result = 1;
	else
		result = 0;
	pthread_mutex_unlock(&philo->data->lock);
	return (result);
}

bool	get_bool(t_data *data, bool *src)
{
	bool	store;

	pthread_mutex_lock(&data->lock);
	store = *src;
	pthread_mutex_unlock(&data->lock);
	return (store);
}

void	*simulation(t_philo *philo)
{
	sleepodd(philo);
	while (1)
	{
		if (breaksim(philo))
		{
			ft_mutex_destroy(philo->data, philo->data->philo_num - 1);
			exit(EXIT_SUCCESS);
		}
		eating_time(philo);
		if (philo->data->philo_num > 1)
		{
			sleeping_time(philo);
			ft_printf(4, philo->data, philo->id);
		}
		else
			ft_usleep(philo->data->dying_time);
	}
	return (NULL);
}
