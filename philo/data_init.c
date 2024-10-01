/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:36:51 by sarif             #+#    #+#             */
/*   Updated: 2024/10/01 10:00:58 by sarif            ###   ########.fr       */
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
		if (pthread_mutex_init(&ph->forks[i], NULL) != 0)
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
			return (0);
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
		ph->philos[i].r_fork = &ph->forks[i];
		ph->philos[i].l_fork = &ph->forks[(i + 1) % ph->philo_num];
		if (!ft_mutex_init(&ph->philos[i].protect, ph))
			return (0);
		if (pthread_create(&ph->philos[i].philo, NULL,
				(void *)simulation, &ph->philos[i]) != 0)
			return (0);
	}
	if (!mentor_creator(ph))
		return (0);
	return (join_philos(ph));
}

int	data_init(t_data *ph)
{
	ph->start_sim = 0;
	ph->dead_flag = false;
	if (ph->philo_num == 0 || ph->meals == 0)
		return (0);
	ph->philos = malloc(sizeof(t_philo) * ph->philo_num);
	if (!ph->philos)
		return (0);
	ph->forks = malloc(ph->philo_num * sizeof(pthread_mutex_t));
	if (!ph->forks)
		return (0);
	if (!ft_mutex_init(&ph->lock, ph) || !ft_mutex_init(&ph->print, ph))
		return (0);
	if (!fork_creator(ph))
		return (0);
	ph->stamp = get_time();
	return (philo_creator(ph));
}
