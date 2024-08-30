/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:38 by sarif             #+#    #+#             */
/*   Updated: 2024/08/30 20:14:39 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleep_oddphilo(t_philo *philo)
{
	if (philo->id % 2 != 0)
		ft_usleep(philo->data->eating_time / 2);
}

void	simulation(t_philo *philo)
{
	pthread_t	*mentor;
	t_data		*data;

	data = philo->data;
	sleep_oddphilo(philo);
	if (pthread_create(&mentor, NULL, (void *)mentor_routine, &philo) != 0)
	{
		free (philo->data->philos);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		sem_wait(data->forks);
		printf("%lu\t%d has taken a fork\n", get_time() - data->stamp, philo->id);
		sem_wait(data->forks);
		printf("%lu\t%d has taken a fork\n", get_time() - data->stamp, philo->id);
		printf("%lu\t%d is eating\n", get_time() - data->stamp, philo->id);
		philo->last_meal = get_time();
		ft_usleep(data->eating_time);
		sem_post(data->forks);
		sem_post(data->forks);
		printf("%lu\t%d is sleeping\n", get_time() - data->stamp, philo->id);
		ft_sleep(data->dying_time);
		printf("%lu\t%d is thinking\n", get_time() - data->stamp, philo->id);
	}
	pthread_join(&mentor, NULL);
}

void	mentor_routine(t_philo	*philo)
{
	int	cur_time;

	cur_time = get_time();
	while (1)
	{
		if (cur_time - philo->last_meal > philo->data->dying_time)
			exit(2);
		if (philo->meals == philo->data->meals)
			exit(0);
	}
}

void	ft_stop_simulation(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_num)
		kill(data->philos[i].pid);
}

void	start_simulation(t_data *data)
{
	int	status;
	int	pid;
	int	i;

	i = -1;
	data->stamp = get_time();
	while (++i < data->philo_num)
	{
		pid = fork();
		if (!pid)
			simulation(&data->philos[i]);
		else
			data->philos[i].pid = pid;
	}
	i = -1;
	while (++i < data->philo_num)
	{
		waitpid(NULL, &status, 0);
		if (WEXITSTATUS(status) == 2)
			ft_stop_simulation(data);
	}
}