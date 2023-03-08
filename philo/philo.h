/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/08 17:35:36 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define bool int
# define true 1
# define false 0

typedef struct s_philo
{
	pthread_t		t_id;
	pthread_mutex_t	l_shield;
	pthread_mutex_t	*r_shield;
	int				l_fork;
	int				*r_fork;
	int				id;
	int				nb_eat;
	long long		last_eat;
	struct s_rules	*rules;
}					t_philo;

typedef struct s_rules
{
	pthread_mutex_t	info;
	int				n_philo;
	long			t_death;
	long			t_eat;
	long			t_sleep;
	int				nb_eat;
	int				current;
	long long		start;
	t_philo			*philo;
}					t_rules;

// Routine
void				eat(t_rules *rules, t_philo *philo);
void				*ft_routine(void *args);
void				create_thread(t_rules *rules);

// Utils
long long			get_time(void);
long long			ft_atol(const char *nptr);
void				init_rules(t_rules *rules, int ac, char **av);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				m_destroy(t_rules *rules);

#endif