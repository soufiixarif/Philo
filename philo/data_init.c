/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:36:51 by sarif             #+#    #+#             */
/*   Updated: 2024/10/08 11:01:46 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mentor_creator(t_data *data)
{
	if (pthread_create(&data->mentor, NULL, (void *)mentor_routine, data) != 0)
		return (0);
	if (pthread_join(data->mentor, NULL) != 0)
		return (0);
	return (1);
}

int	fork_creator(t_data *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_num)
	{
		if (ft_mutex_init(&ph->forks[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	join_philos(t_data *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_num)
	{
		if (pthread_join(ph->philos[i].philo, NULL) != 0)
			return (free(ph->philos), free(ph->forks), 0);
		i++;
	}
	return (1);
}

int	philo_creator(t_data *ph)
{
	int			i;

	i = -1;
	while (++i < ph->philo_num)
	{
		ph->philos[i].id = i + 1;
		ph->philos[i].last_meal = get_time();
		ph->philos[i].meals = 0;
		ph->philos[i].data = ph;
		ph->philos[i].sleeptime = ph->sleeping_time;
		ph->philos[i].r_fork = &ph->forks[i].mtx;
		ph->philos[i].l_fork = &ph->forks[(i + 1) % ph->philo_num].mtx;
		if (!ft_mutex_init(&ph->philos[i].protect))
			return (free(ph->philos), free(ph->forks), 0);
		if (pthread_create(&ph->philos[i].philo, NULL,
				(void *)simulation, &ph->philos[i]) != 0)
			return (free(ph->philos), free(ph->forks), 0);
	}
	if (!mentor_creator(ph))
		return (free(ph->philos), free(ph->forks), 0);
	return (join_philos(ph));
}

int	data_init(t_data *ph)
{
	ph->dead_flag = false;
	if (ph->philo_num == 0 || ph->meals == 0)
		return (0);
	ph->philos = malloc(sizeof(t_philo) * ph->philo_num);
	if (!ph->philos)
		return (0);
	ph->forks = malloc(ph->philo_num * sizeof(pthread_mutex_t));
	if (!ph->forks)
		return (free(ph->philos), 0);
	if (!ft_mutex_init(&ph->lock) || !ft_mutex_init(&ph->print))
		return (free(ph->philos), free(ph->forks), 0);
	if (!fork_creator(ph))
		return (free(ph->philos), free(ph->forks), 0);
	ph->s_sim = get_time();
	return (philo_creator(ph));
}
