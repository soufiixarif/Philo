/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:47:21 by sarif             #+#    #+#             */
/*   Updated: 2024/09/16 21:53:09 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_printf(t_data *d, int id, long time, char *action)
{
	sem_wait(d->ft_printf);
	printf("%lu\t%d %s\n", time, id, action);
	if (action[0] != 'd')
		sem_post(d->ft_printf);
}

void	ft_wait_pid(t_data *data)
{
	unsigned int	i;
	int	status;

	i = 0;
	while (i < data->philo_num)
	{
		waitpid((long)NULL, &status, 0);
		if (WEXITSTATUS(status) == 2)
		{
			ft_stop_simulation(data);
			break ;
		}
		i++;
	}
}

void	ft_exit_prog(t_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->philo_num)
	{
		sem_close(data->philos[i].philo_sem);
		sem_unlink(data->philos[i].philo_name);
		i++;
	}
	sem_close(data->forks);
	sem_close(data->ft_printf);
	sem_unlink("/forks");
	sem_unlink("/ft_printf");
}
