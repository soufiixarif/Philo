/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:50 by sarif             #+#    #+#             */
/*   Updated: 2024/08/30 20:15:10 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	data_init(t_data *data)
{
	int	i;

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
		data->philos[i].last_meal = get_time();
	}
	sem_init(data->forks, 0, data->philo_num);
	start_simulation(data);
}
