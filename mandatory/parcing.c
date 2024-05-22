/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:29:18 by sarif             #+#    #+#             */
/*   Updated: 2024/05/21 12:10:14 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	checkvalidity(char *s)
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

void    parcing_data(int ac, char **av, t_data *ph)
{
    int i;

    i = 1;
    while (i < ac)
    {
        if (!checkvalidity(av[i++]))
            exit(write(2, "args error",10));
    }
    
    ph->philo_num = ft_atoi(av[1]);
    ph->dying_time = ft_atoi(av[2]) * 1000;
    ph->eating_time = ft_atoi(av[3]) * 1000;
    ph->sleeping_time = ft_atoi(av[4]) * 1000;
	if (ph->dying_time < 6e4 || ph->eating_time < 6e4 ||
		ph->sleeping_time < 6e4)
		exit(write(2, "args error",10));
    if (ac == 6)
    {
        if (!checkvalidity(av[5]))
            exit(write(2, "args error",10));
        else
            ph->meals = ft_atoi(av[5]);
    }
}
