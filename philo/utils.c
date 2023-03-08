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

long long get_time() 
{
	return (0);
    // struct timeval current_time;
	
    // gettimeofday(&current_time, NULL);
    // long long ms;
	// ms = current_time.tv_sec * 1000LL + current_time.tv_usec / 1000LL;
    // return (ms);
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
	memset(rules, 0, sizeof(t_rules));
	rules->start = get_time();
	rules->t_death = ft_atol(av[2]);
	rules->t_eat = ft_atol(av[3]);
	rules->t_sleep = ft_atol(av[4]);
	rules->n_philo = ft_atol(av[1]);
	pthread_mutex_init(&rules->info, NULL);
	if (ac == 6)
		rules->nb_eat = ft_atol(av[5]);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}

void	m_destroy(t_rules *rules)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&rules->info);
	while (++i < rules->n_philo)
	{
		pthread_mutex_destroy(&rules->philo[i].l_shield);
	}
}
