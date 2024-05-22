/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:51:58 by sarif             #+#    #+#             */
/*   Updated: 2024/05/13 18:42:24 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_check_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

long	ft_atoi(char *str)
{
	int		i;
	long	r;
    int 	s;

	i = 0;
	s = 1;
	r = 0;
	while (((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)) && str[i])
		i++;
	s = ft_check_sign(str, &i);
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		r = (r * 10) + (str[i] - '0');
		i++;
	}
	return ((r * s));
}