/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 16:02:28 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/10 15:17:44 by tedelin          ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		t_id;
	pthread_mutex_t	n_eat;
	pthread_mutex_t	death;
	pthread_mutex_t	l_eat;
	int				l_fork;
	int				r_fork;
	int				id;
	int				nb_eat;
	long long		last_eat;
	int				is_dead;
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
	long long		start;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_rules;

// Routine
void				*ft_routine(void *args);
void				create_thread(t_rules *rules);
void				ft_eat(t_rules *rules, t_philo *philo);

// Init
void				init_rules(t_rules *rules, int ac, char **av);
void				init_philo(t_rules *rules);

// Handle death
int					check_meal(t_rules *rules);
void				*ft_death(void *args);

// Utils
long long			get_time(void);
long long			ft_atol(const char *nptr);
void				ft_free(t_rules *rules);
void				logs(t_philo *philo, char *message);
int					ft_args(int ac, char **av);
void				ft_usleep(long long time);

#endif