/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:26:43 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/10 11:13:56 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logs(t_philo *philo, char *message)
{
	long long	time;

	pthread_mutex_lock(&philo->rules->info);
	time = get_time() - philo->rules->start;
	printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->rules->info);
}

long long	get_time(void)
{
	long long		ms;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000LL + current_time.tv_usec / 1000LL;
	return (ms);
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

void	ft_free(t_rules *rules)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&rules->info);
	while (++i < rules->n_philo)
		pthread_mutex_destroy(&rules->forks[i]);
	free(rules->philo);
	free(rules->forks);
}

int	ft_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (ac < 5 || ac > 6)
		return (0);
	while (i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
		i++;
	}
	return (1);
}