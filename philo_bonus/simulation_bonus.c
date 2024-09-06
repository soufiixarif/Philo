/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:38 by sarif             #+#    #+#             */
/*   Updated: 2024/09/06 22:41:10 by sarif            ###   ########.fr       */
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
		printf("%lu\t%d has taken a fork\n", ft_get_time() - data->stamp, philo->id);
		sem_wait(data->forks);
		printf("%lu\t%d has taken a fork\n", ft_get_time() - data->stamp, philo->id);
		printf("%lu\t%d is eating\n", ft_get_time() - data->stamp, philo->id);
		philo->last_meal = ft_get_time();
		ft_usleep(data->eating_time);
		philo->meals++;
		sem_post(data->forks);
		sem_post(data->forks);
		printf("%lu\t%d is sleeping\n", ft_get_time() - data->stamp, philo->id);
		ft_usleep(data->sleeping_time);
		printf("%lu\t%d is thinking\n", ft_get_time() - data->stamp, philo->id);
	}
	pthread_join(mentor, NULL);
}

void	mentor_routine(t_philo *philo)
{
	size_t	cur_time;

	while (1)
	{
		cur_time = ft_get_time();
		if (cur_time - philo->last_meal > philo->data->dying_time)
		{
			printf("%lu\t%d died\n", cur_time - philo->data->stamp, philo->id);
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
	int				*store;
	int				pid;
	unsigned int	i;

	i = -1;
	store = malloc(sizeof (pid_t) * data->philo_num);
	data->stamp = ft_get_time();
	while (++i < data->philo_num)
	{
		pid = fork();
		if (!pid)
			simulation(&data->philos[i]);
		data->philos[i].pid = pid;
		store[i] = pid;
	}
	i = -1;
	while (++i < data->philo_num)
	{
		waitpid((pid_t)NULL, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			ft_stop_simulation(data);
			break ;
		}
	}
	sem_close(data->forks);
	sem_unlink("/forks");
}
