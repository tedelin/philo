/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:59:11 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/22 16:50:11 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philo(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 == 0)
		ft_usleep(philo->rules->t_eat / 10);
	while (1)
	{
		if (ft_eat(philo) || my_meal(philo))
			break ;
		ft_logs(philo, "is sleeping");
		ft_usleep(philo->rules->t_sleep);
		ft_logs(philo, "is thinking");
		pthread_mutex_lock(&philo->rules->death);
		if (philo->rules->death_flag == 1)
		{
			pthread_mutex_unlock(&philo->rules->death);
			break ;
		}
		pthread_mutex_unlock(&philo->rules->death);
		ft_usleep(((philo->rules->t_death - \
		(philo->rules->t_eat + philo->rules->t_sleep)) / 2));
	}
	return (NULL);
}

int	check_meal(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < rules->n_philo)
	{
		pthread_mutex_lock(&rules->philo[i].eat_info);
		if (rules->philo[i].nb_eat < rules->nb_eat)
		{
			pthread_mutex_unlock(&rules->philo[i].eat_info);
			return (0);
		}
		pthread_mutex_unlock(&rules->philo[i].eat_info);
	}
	return (1);
}

int	check_death(t_rules *rules, int i)
{
	long long	time;

	pthread_mutex_lock(&rules->philo[i].eat_info);
	time = get_time() - rules->philo[i].last_eat;
	if (time >= rules->t_death)
	{
		pthread_mutex_unlock(&rules->philo[i].eat_info);
		pthread_mutex_lock(&rules->death);
		rules->death_flag = 1;
		pthread_mutex_unlock(&rules->death);
		ft_logs(&rules->philo[i], "died");
		return (1);
	}
	pthread_mutex_unlock(&rules->philo[i].eat_info);
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
		ft_usleep(1);
	}
	return (NULL);
}

int	ft_thread(t_rules *rules)
{
	pthread_t	id_err;
	int			i;

	i = -1;
	while (++i < rules->n_philo)
		if (pthread_create(&rules->philo[i].t_id, NULL, ft_philo,
				&rules->philo[i]))
			return (ft_free(rules, T_ERR, 4, -1));
	if (pthread_create(&id_err, NULL, ft_death, rules))
		return (ft_free(rules, T_ERR, 4, -1));
	i = -1;
	while (++i < rules->n_philo)
		if (pthread_join(rules->philo[i].t_id, NULL))
			return (2);
	if (pthread_join(id_err, NULL))
		return (2);
	return (ft_free(rules, NULL, 4, -1));
}
