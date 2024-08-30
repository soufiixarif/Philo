/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:14:45 by sarif             #+#    #+#             */
/*   Updated: 2024/08/30 20:14:46 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	nb_content(char *s, int len, int i)
{
	int	j;

	j = i;
	while (s[i] && i <= len)
	{
		if (i == j && s[j] == '+')
		{
			i++;
			if (s[i] == 32 || s[i] == '\t' || s[i] == '\0')
				return (0);
			continue ;
		}
		else if (s[i] >= '0' && s[i++] <= '9')
			continue ;
		else
			return (0);
		i++;
	}
	return (1);
}

static int	checkvalidity(char *s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	len--;
	while (s[i] == 32 || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[len] == 32 || (s[len] == '\t' && len >= 0))
	{
		if (s[len] == 32 || s[len] == '\t')
			len--;
		else
			break ;
	}
	if (!nb_content(s, len, i))
		return (0);
	return (1);
}

void	parcing_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!checkvalidity(av[i++]))
			exit(write(2, "args error", 10));
	}
	data->philo_num = ft_atoi(av[1]);
	data->dying_time = ft_atoi(av[2]);
	data->eating_time = ft_atoi(av[3]);
	data->sleeping_time = ft_atoi(av[4]);
	data->meals = -1;
	if (data->dying_time < 60 || data->eating_time < 60 || \
	data->sleeping_time < 60)
		exit(write(2, "args error", 10));
	if (ac == 6)
	{
		if (!checkvalidity(av[5]))
			exit(write(2, "args error", 10));
		else
			data->meals = ft_atoi(av[5]);
	}
}
