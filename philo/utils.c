/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:26:43 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/08 17:23:03 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	logs(t_philo *philo, char *message)
{
	long long time;

	time = get_time() - philo->rules->start;
	pthread_mutex_lock(&philo->rules->info);
	printf("%lld %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(&philo->rules->info);
}

long long get_time() 
{
    struct timeval current_time;
	
    gettimeofday(&current_time, NULL);
    long long ms;
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

void	init_rules(t_rules *rules, int ac, char **av)
{
	int	i;

	i = -1;
	memset(rules, 0, sizeof(t_rules));
	rules->start = get_time();
	rules->t_death = ft_atol(av[2]);
	rules->t_eat = ft_atol(av[3]);
	rules->t_sleep = ft_atol(av[4]);
	rules->n_philo = ft_atol(av[1]);
	pthread_mutex_init(&rules->info, NULL);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return ; // add protection
	while (++i < rules->n_philo)
		pthread_mutex_init(&rules->forks[i], NULL);
	if (ac == 6)
		rules->nb_eat = ft_atol(av[5]);
}

void	m_destroy(t_rules *rules)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&rules->info);
	while (++i < rules->n_philo)
		pthread_mutex_destroy(&rules->forks[i]);
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
