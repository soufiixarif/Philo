/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:38 by sarif             #+#    #+#             */
/*   Updated: 2024/09/14 19:59:03 by sarif            ###   ########.fr       */
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
	pthread_t	mentor;
	t_data		*data;

	data = philo->data;
	sleep_oddphilo(philo);
	if (pthread_create(&mentor, NULL, (void *)mentor_routine, philo) != 0)
	{
		free (philo->data->philos);
		exit(EXIT_FAILURE);
	}
	philo->last_meal = ft_get_time();
	while (1)
	{
		sem_wait(data->forks);
		ft_printf(data, philo->id, ft_get_time() - data->stamp, T_FORK);
		sem_wait(data->forks);
		ft_printf(data, philo->id, ft_get_time() - data->stamp, T_FORK);
		ft_printf(data, philo->id, ft_get_time() - data->stamp, EAT);
		philo->last_meal = ft_get_time();
		ft_usleep(data->eating_time);
		sem_post(data->forks);
		sem_post(data->forks);
		ft_printf(data, philo->id, ft_get_time() - data->stamp, SLEEP);
		ft_usleep(data->sleeping_time);
		philo->meals++;
		ft_printf(data, philo->id, ft_get_time() - data->stamp, THINK);
	}
	pthread_join(mentor, NULL);
}

void	mentor_routine(t_philo *philo)
{
	size_t	cur_time;

	ft_usleep(philo->data->dying_time / 2);
	while (1)
	{
		cur_time = ft_get_time();
		if (cur_time - philo->last_meal > philo->data->dying_time)
		{
			ft_printf(philo->data, philo->id, cur_time - philo->data->stamp, DEAD);
			exit(2);
		}
		if (philo->data->meals != -1 && (philo->meals >= philo->data->meals))
			exit(0);
	}
}

void	ft_stop_simulation(t_data *data)
{
	unsigned int	i;

	i = -1;
	while (++i < data->philo_num)
		kill(data->philos[i].pid, SIGINT);
}

void	start_simulation(t_data *data)
{
	int				status;
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
	i = -1;
	while (++i < data->philo_num)
	{
		waitpid((long)NULL, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			ft_stop_simulation(data);
			break ;
		}
	}
	sem_close(data->forks);
	sem_close(data->ft_printf);
	sem_unlink("/forks");
	sem_unlink("/ft_printf");
}
