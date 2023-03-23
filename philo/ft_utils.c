/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:26:43 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/23 08:34:36 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

long long	ft_atol(const char *nptr)
{
	long long	res;
	int			sign;

	res = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r') || *nptr == '\n')
		nptr++;
	if (*nptr == '-')
		sign = -sign;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		res = (res * 10) + (*nptr - '0');
		nptr++;
	}
	return (res * sign);
}

int	ft_free(t_rules *rules, char *msg, int error, int index)
{
	int	i;

	i = -1;
	if (index == -1)
		index = rules->n_philo;
	if (error > 0)
		pthread_mutex_destroy(&rules->logs);
	if (error > 1)
		pthread_mutex_destroy(&rules->death);
	while ((error > 2 && ++i < index) || (error > 3 && i < rules->n_philo))
		pthread_mutex_destroy(&rules->forks[i]);
	i = -1;
	while (error > 3 && ++i < index)
		pthread_mutex_destroy(&rules->philo[i].eat_info);
	if (rules->forks)
		free(rules->forks);
	if (rules->philo)
		free(rules->philo);
	if (msg)
		return (printf("%s\n", msg), 1);
	return (0);
}

int	ft_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (1);
	while (i < ac)
	{
		j = -1;
		if (av[i] && av[i][++j] != '+' && (av[i][j] < '0' || av[i][j] > '9'))
			return (1);
		if (av[i] && av[i][j] == '+' && !av[i][j + 1])
			return (1);
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		i++;
	}
	return (0);
}
