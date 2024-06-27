/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:36:51 by sarif             #+#    #+#             */
/*   Updated: 2024/06/28 00:36:51 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mentor_creator(t_data *data)
{
	data->mentor = malloc(sizeof (pthread_t));
	if (!data->mentor)
	{
		ft_mutex_destroy(data, data->philo_num - 1);
		(free(data->forks), free(data->philos));
	}
	if (pthread_create(&data->mentor, NULL, (void *)mentor_routine, data) != 0)
	{
		ft_mutex_destroy(data, data->philo_num - 1);
		(free(data->forks), free(data->philos));
		exit(EXIT_FAILURE);
	}
	if (pthread_join(data->mentor, NULL) != 0)
	{
		ft_mutex_destroy(data, data->philo_num - 1);
		(free(data->forks), free(data->philos));
		exit(EXIT_FAILURE);
	}
}

void	fork_creator(t_data *ph)
{
	int	i;

	i = -1;
	while (i < ph->philo_num)
	{
		if (pthread_mutex_init(&ph->forks[i], NULL) != 0)
		{
			ft_mutex_destroy(ph, i - 1);
			(free(ph->forks), free(ph->philos));
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	join_philos(t_data *ph)
{
	int	i;

	i = 0;
	while (i < ph->philo_num)
	{
		if (pthread_join(ph->philos[i].philo, NULL) != 0)
		{
			ft_mutex_destroy(ph, ph->philo_num - 1);
			(free(ph->forks), free(ph->philos));
			exit(EXIT_FAILURE);
		}
	}
}

void	philo_creator(t_data *ph)
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
		if (pthread_create(&ph->philos[i].philo, NULL,
				(void *)simulation, &ph->philos[i]) != 0)
		{
			ft_mutex_destroy(ph, ph->philo_num - 1);
			(free(ph->forks), free(ph->philos));
			exit(EXIT_FAILURE);
		}
	}
	mentor_creator(ph);
	join_philos(ph);
}

void	data_init(t_data *ph)
{
	ph->start_sim = 0;
	ph->dead_flag = false;
	if (ph->philo_num == 0 || ph->meals == 0)
		return ;
	ph->philos = malloc(sizeof(t_philo) * ph->philo_num);
	if (!ph->philos)
		return ;
	ph->forks = malloc(ph->philo_num * sizeof(pthread_mutex_t));
	if (!ph->forks)
	{
		free(ph->philos);
		return ;
	}
	fork_creator(ph);
	ph->stamp = get_time();
	philo_creator(ph);
}
