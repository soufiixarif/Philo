/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:36:58 by sarif             #+#    #+#             */
/*   Updated: 2024/09/28 16:35:18 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philo philo, t_data *ph, int *cnt)
{
	if (ph->meals != -1 && philo.meals >= ph->meals)
		return ((*cnt)++, 1);
	return (0);
}

void	mentor_routine(t_data *ph)
{
	int	i;
	int	cnt;

	while (1)
	{
		(1) && (i = -1, cnt = 0);
		while (++i < ph->philo_num)
		{
			pthread_mutex_lock(&ph->lock);
			pthread_mutex_lock(&ph->philos[i].protect);
			if (!is_full(ph->philos[i], ph, &cnt)
				&& get_time() - ph->philos[i].last_meal > ph->dying_time)
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
		if (cnt == ph->philo_num)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_data	ph;

	if (ac == 5 || ac == 6)
	{
		parcing_data(ac, av, &ph);
		if (!data_init(&ph))
			return (1);
	}
	else
		printf("args error\n");
	pthread_mutex_destroy(&ph.lock);
	pthread_mutex_destroy(&ph.print);
	ft_mutex_destroy(&ph, ph. philo_num - 1);
	(free(ph.forks), free(ph.philos));
	return (0);
}
