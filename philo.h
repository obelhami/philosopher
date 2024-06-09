#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // usleep
#include <stdbool.h> // bool
#include <pthread.h> // pthread_create, pthread_join, pthread_mutex_t
#include <sys/time.h> // gettimeofday, struct timeval
#include <string.h> // memset

typedef struct s_table t_table;

typedef struct s_fork
{
    int id;
    pthread_mutex_t mutex;
} t_fork;

typedef struct s_philo
{
    int id;
    long meals_counter;
    bool full;
    long last_meal_time;
    t_fork *left_fork;
    t_fork *right_fork;
    pthread_t thread_id;
    t_table *table;
} t_philo;


struct s_table
{
    long    nbr_philosophers;
    long    time_to_eat;
    long    time_to_sleep;
    long    time_to_die;
    long    nbr_limit_meals;
    long    start_simmulation;
    bool    end_simmulation;
    t_fork  *forks; //array of forks 
    t_philo *philos; // array of philos
};

void error(char *msg);
void parsing(int argc, char **argv, t_table *table);
long ft_atol(char *str);
void    fill_struct(t_table *table, int i, char *arg);

#endif