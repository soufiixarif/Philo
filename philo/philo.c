/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 00:36:58 by sarif             #+#    #+#             */
/*   Updated: 2024/10/08 20:45:36 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_full(t_philo philo, t_data *ph, int *cnt)
{
	if (ph->meals != -1 && philo.meals >= ph->meals)
		return ((*cnt)++, 1);
	return (0);
}

void	mutex_unlock_norm(t_data *ph, t_philo *philo)
{
	pthread_mutex_unlock(&ph->lock.mtx);
	pthread_mutex_unlock(&philo->protect.mtx);
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
			pthread_mutex_lock(&ph->lock.mtx);
			pthread_mutex_lock(&ph->philos[i].protect.mtx);
			if (!is_full(ph->philos[i], ph, &cnt)
				&& get_time() - ph->philos[i].last_meal > ph->dying_time)
			{
				ph->dead_flag = true;
				ft_printf(5, ph, ph->philos[i].id);
				mutex_unlock_norm(ph, &ph->philos[i]);
				return ;
			}
			mutex_unlock_norm(ph, &ph->philos[i]);
		}
		if (cnt == ph->philo_num)
			break ;
		ft_usleep(50);
	}
}

int	main(int ac, char **av)
{
	t_data	ph;

	if (ac == 5 || ac == 6)
	{
		if (!parcing_data(ac, av, &ph))
			return (write(1, "args error\n", 11));
		if (ph.philo_num == 0 || ph.meals == 0)
			return (1);
		if (!data_init(&ph))
		{
			ft_mutex_destroy(&ph, ph.philo_num - 1);
			return (1);
		}
	}
	else
		return (printf("args error\n"));
	ft_mutex_destroy(&ph, ph. philo_num - 1);
	(free(ph.forks), free(ph.philos));
	return (0);
}
