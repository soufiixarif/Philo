/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 20:21:53 by sarif             #+#    #+#             */
/*   Updated: 2024/05/20 20:11:28 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct s_data
{
	long	philo_num;
	long	dying_time;
	long	eating_time;
	long	sleeping_time;
	long	meals;
	long	start_sim;
	bool	end_sim;
} t_data;

//philo----------------------------------------------
void    parcing_data(int ac, char **av, t_data *ph);
int     checkvalidity(char *s);
void	start_simulation(t_data *ph);
void	simulation(t_data *ph);



//libft----------------------------------------------
long	ft_atoi(char *str);
size_t	ft_strlen(char *s);

#endif