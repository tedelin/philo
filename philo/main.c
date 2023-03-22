/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:21 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/22 17:11:52 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_rules(t_rules *rules, int ac, char **av)
{
	memset(rules, 0, sizeof(t_rules));
	rules->n_philo = ft_atol(av[1]);
	rules->t_death = ft_atol(av[2]);
	rules->t_eat = ft_atol(av[3]);
	rules->t_sleep = ft_atol(av[4]);
	rules->nb_eat = -1;
	if (ac == 6)
		rules->nb_eat = ft_atol(av[5]);
	if (rules->nb_eat == 0)
		return (1);
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->n_philo);
	rules->philo = malloc(sizeof(t_philo) * rules->n_philo);
	if (!rules->forks || !rules->philo)
		return (ft_free(rules, MALLOC_ERR, 0, 0), 1);
	memset(rules->philo, 0, sizeof(t_philo) * rules->n_philo);
	if (init_mutex(rules))
		return (1);
	init_philo(rules);
	return (0);
}

int	init_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&rules->logs, NULL))
		return (ft_free(rules, M_ERR, 0, 0), 1);
	if (pthread_mutex_init(&rules->death, NULL))
		return (ft_free(rules, M_ERR, 1, 0), 1);
	while (++i < rules->n_philo)
		if (pthread_mutex_init(&rules->forks[i], NULL))
			return (ft_free(rules, M_ERR, 3, i), 1);
	i = -1;
	while (++i < rules->n_philo)
		if (pthread_mutex_init(&rules->philo[i].eat_info, NULL))
			return (ft_free(rules, M_ERR, 4, i), 1);
	return (0);
}

int	init_philo(t_rules *rules)
{
	int	i;

	i = -1;
	rules->start = get_time();
	while (++i < rules->n_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].rules = rules;
		rules->philo[i].l_fork = i;
		rules->philo[i].last_eat = rules->start;
		rules->philo[i].r_fork = (i + 1) % rules->n_philo;
	}
	ft_thread(rules);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	rules;

	if (ft_args(ac, av) || ac < 5 || ac > 6)
	{
		printf("%s\n", ARGS_ERR);
		return (0);
	}
	init_rules(&rules, ac, av);
	return (0);
}
