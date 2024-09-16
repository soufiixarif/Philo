/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:47:21 by sarif             #+#    #+#             */
/*   Updated: 2024/09/14 19:53:23 by sarif            ###   ########.fr       */
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
