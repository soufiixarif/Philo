/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:50 by sarif             #+#    #+#             */
/*   Updated: 2024/09/06 22:23:57 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_data *data)
{
	unsigned int	i;

	i = -1;
	data->philos = malloc(sizeof (t_philo) * data->philo_num);
	if (!data->philos)
		return ;
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].meals = 0;
		data->philos[i].sleeptime = data->sleeping_time;
	}
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->philo_num);
	if (data->forks == SEM_FAILED)
	{
		perror("Failed to open semaphore");
		exit(EXIT_FAILURE);
	}
	start_simulation(data);
}
