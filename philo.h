#ifndef PHILO_H
#define PHILO_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // usleep
#include <stdbool.h> // bool
#include <pthread.h> // pthread_create, pthread_join, pthread_mutex_t
#include <sys/time.h> // gettimeofday, struct timeval
#include <string.h> // memset

#define M_LOCK pthread_mutex_lock
#define M_UNLOCK pthread_mutex_unlock
#define M_INIT pthread_mutex_init

typedef struct s_table t_table;

typedef struct s_philo
{
    pthread_t th;
    int id;
    long meals_counter;
    bool full;
    long last_meal_time;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
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
    pthread_mutex_t mutex;
    pthread_mutex_t  *forks; //array of forks 
    t_philo *philos; // array of philos
};


int parsing(int argc, char **argv, t_table *table);
long ft_atol(char *str);
void    fill_struct(t_table *table, long i, char *arg);

void *routine(void *philo);


long get_time();
void  ft_sleep(long time);

#endif