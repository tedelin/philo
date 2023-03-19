/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:21 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/19 19:39:54 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_rules(t_rules *rules, int ac, char **av)
{
	int	i;

	i = -1;
	memset(rules, 0, sizeof(t_rules));
	rules->n_philo = ft_atol(av[1]);
	if (rules->n_philo > 200 || rules->n_philo <= 0)
		return (printf("%s\n", PHILO_ERR), 1);
	rules->t_death = ft_atol(av[2]);
	rules->t_eat = ft_atol(av[3]);
	rules->t_sleep = ft_atol(av[4]);
	rules->nb_eat = -1;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	if (!rules->forks)
		return (printf("%s\n", MALLOC_ERR), 1);
	pthread_mutex_init(&rules->logs, NULL);
	pthread_mutex_init(&rules->death, NULL);
	while (++i < rules->n_philo)
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (free(rules->forks), printf("%s\n", M_ERR), 1);
	if (ac == 6)
		rules->nb_eat = ft_atol(av[5]);
	init_philo(rules);
	return (0);
}

int	init_philo(t_rules *rules)
{
	int	i;

	i = -1;
	rules->philo = malloc(sizeof(t_philo) * rules->n_philo);
	if (!rules->philo)
		return (free(rules->forks), printf("%s\n", MALLOC_ERR), 1);
	memset(rules->philo, 0, sizeof(t_philo) * rules->n_philo);
	rules->start = get_time();
	while (++i < rules->n_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].rules = rules;
		rules->philo[i].l_fork = i;
		rules->philo[i].last_eat = rules->start;
		rules->philo[i].r_fork = (i + 1) % rules->n_philo;
		if (pthread_mutex_init(&rules->philo[i].eat_info, NULL))
			return (free(rules->forks), free(rules->philo), printf("%s\n", M_ERR), 1);
	}
	ft_thread(rules);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (!ft_args(ac, av) || ac < 5 || ac > 6)
		return (printf("%s\n", ARGS_ERR), 0);
	init_rules(&rules, ac, av);
	return (0);
}
