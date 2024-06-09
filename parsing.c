#include "philo.h"

int    check_arg(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '+' && i == 0 && arg[i + 1] >= '0' && arg[i + 1] <= '9')
            i++;
        if (arg[i] < '0' || arg[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void    fill_struct(t_table *table, int i, char *arg)
{
    if (i == 1)
        table->nbr_philosophers = ft_atol(arg);
    if (i == 2)
        table->time_to_die = ft_atol(arg);
    if (i == 3)
        table->time_to_eat = ft_atol(arg);
    if (i == 4)
        table->time_to_sleep = ft_atol(arg);
    if (i == 5)
        table->nbr_limit_meals = ft_atol(arg);
}
void    chack_int_max(char **argv)
{
    int i;

    i = 1;
    while (i < 6)
    {
        if (ft_atol(argv[i]) > 2147483647)
        {
            printf("Error: argument is too big\n");
            exit(1);
        }
        i++;
    }
    i = 1;
    while (i < 6)
    {
        if (ft_atol(argv[i]) < 0)
        {
            printf("Error: argument is negative\n");
            exit(1);
        }
        i++;
    }
}

void    parsing(int argc, char **argv, t_table *table)
{
    int i;

    i = 1;
    chack_int_max(argv);
    while (i < argc)
    {
        if (check_arg(argv[i]) == 0)
        {
            printf("Error: wrong argument\n");
            exit(1);
        }
        fill_struct(table, i, argv[i]);
        i++;
    }
}