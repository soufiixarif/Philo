/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:38 by sarif             #+#    #+#             */
/*   Updated: 2024/09/25 11:45:04 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_eat_action(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	ft_printf(data, philo->id, ft_get_time() - data->stamp, T_FORK);
	sem_wait(data->forks);
	ft_printf(data, philo->id, ft_get_time() - data->stamp, T_FORK);
	sem_wait(philo->philo_sem);
	philo->last_meal = ft_get_time();
	philo->meals++;
	sem_post(philo->philo_sem);
	ft_printf(data, philo->id, ft_get_time() - data->stamp, EAT);
	ft_usleep(data->eating_time);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	simulation(t_philo *philo)
{
	t_data		*data;
	pthread_t	mentor;

	mentor = NULL;
	data = philo->data;
	if (data->philo_num > 1)
		sleep_oddphilo(philo);
	mentor_creator(data, mentor, philo);
	philo->last_meal = ft_get_time();
	while (1)
	{
		if (philo->meals == philo->data->meals)
			exit(0);
		ft_eat_action(philo, data);
		if (data->philo_num > 1)
		{
			ft_printf(data, philo->id, ft_get_time() - data->stamp, SLEEP);
			ft_usleep(data->sleeping_time);
			ft_printf(data, philo->id, ft_get_time() - data->stamp, THINK);
		}
		else
			ft_usleep(data->dying_time);
	}
	pthread_join(mentor, NULL);
}

void	mentor_routine(t_philo *philo)
{
	long	cur_time;
	t_data	*data;

	data = philo->data;
	ft_usleep(philo->data->dying_time / 2);
	while (1)
	{
		cur_time = ft_get_time();
		sem_wait(philo->philo_sem);
		if (cur_time - philo->last_meal > data->dying_time)
		{
			ft_printf(philo->data, philo->id, cur_time - data->stamp, DEAD);
			sem_post(philo->philo_sem);
			sem_close(philo->philo_sem);
			sem_unlink(philo->philo_name);
			free(philo->philo_name);
			sem_close(data->forks);
			sem_unlink("/forks");
			free(data->philos);
			exit(2);
		}
		sem_post(philo->philo_sem);
	}
}

void	ft_stop_simulation(t_data *data)
{
	unsigned int	i;

	i = -1;
	while (++i < data->philo_num)
	{
		kill(data->philos[i].pid, SIGINT);
	}
}

void	start_simulation(t_data *data)
{
	int				pid;
	unsigned int	i;

	i = -1;
	data->stamp = ft_get_time();
	while (++i < data->philo_num)
	{
		pid = fork();
		if (!pid)
			simulation(&data->philos[i]);
		else if (pid > 0)
			data->philos[i].pid = pid;
	}
	ft_wait_pid(data);
	ft_clean_prog(data);
}
