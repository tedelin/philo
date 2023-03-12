/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:59:11 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/12 11:06:45 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_philo(void *args)
{
	t_philo	philo;
	t_rules	*rules;

	philo = *(t_philo *)args;
	rules = philo.rules;
	while (1)
	{
		ft_eat(rules, &philo);
		if (rules->nb_eat != -1 && philo.nb_eat == rules->nb_eat)
			break ;
		logs(&philo, "is sleeping");
		ft_usleep(rules->t_sleep);
		logs(&philo, "is thinking");
		pthread_mutex_lock(&rules->death);
		if (rules->death_flag == 1)
		{
			pthread_mutex_unlock(&rules->death);
			break ;
		}
		pthread_mutex_unlock(&rules->death);
	}
	return (NULL);
}

int	check_meal(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->philo[i].n_eat);
		if (rules->philo[i].nb_eat < rules->nb_eat)
		{
			pthread_mutex_unlock(&rules->philo[i].n_eat);
			return (0);
		}
		pthread_mutex_unlock(&rules->philo[i].n_eat);
	}
	return (1);
}

int	check_death(t_rules *rules, int i)
{
	pthread_mutex_lock(&rules->philo[i].l_eat);
	if (get_time() - rules->philo[i].last_eat >= rules->t_death)
	{
		pthread_mutex_unlock(&rules->philo[i].l_eat);
		pthread_mutex_lock(&rules->death);
		rules->death_flag = 1;
		pthread_mutex_unlock(&rules->death);
		logs(&rules->philo[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&rules->philo[i].l_eat);
	return (0);
}

void	*ft_death(void *args)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)args;
	while (1)
	{
		if (rules->nb_eat != -1 && check_meal(rules))
			break ;
		i = -1;
		while (++i < rules->n_philo)
			if (check_death(rules, i))
				return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	ft_thread(t_rules *rules)
{
	pthread_t	id_err;
	int			i;

	rules->philo = malloc(sizeof(t_philo) * rules->n_philo);
	memset(rules->philo, 0, sizeof(t_philo) * rules->n_philo);
	init_philo(rules);
	i = -1;
	pthread_create(&id_err, NULL, ft_death, rules);
	while (++i < rules->n_philo)
		pthread_create(&rules->philo[i].t_id, NULL, ft_philo,
			&rules->philo[i]);
	pthread_join(id_err, NULL);
	i = -1;
	while (++i < rules->n_philo)
		pthread_join(rules->philo[i].t_id, NULL);
	ft_free(rules);
}
