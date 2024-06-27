/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:36:58 by sarif             #+#    #+#             */
/*   Updated: 2024/06/28 00:36:58 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mentor_routine(t_data *ph)
{
	int		cur_time;
	int		i;

	while (1)
	{
		i = -1;
		while (++i < ph->philo_num)
		{
			pthread_mutex_lock(&ph->lock);
			pthread_mutex_lock(&ph->philos[i].protect);
			cur_time = get_time();
			if (cur_time - ph->philos[i].last_meal > ph->dying_time)
			{
				ph->dead_flag = true;
				ft_printf(5, ph, ph->philos[i].id);
				pthread_mutex_unlock(&ph->lock);
				pthread_mutex_unlock(&ph->philos[i].protect);
				return ;
			}
			pthread_mutex_unlock(&ph->philos[i].protect);
			pthread_mutex_unlock(&ph->lock);
		}
	}
}

int	main(int ac, char **av)
{
	t_data	ph;

	if (ac == 5 || ac == 6)
	{
		parcing_data(ac, av, &ph);
		data_init(&ph);
	}
	else
		printf("args error\n");
	return (0);
}
