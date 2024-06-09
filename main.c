#include "philo.h"

void error(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

void    ft_init_table(t_table *table) {
    if(table) {
        table->end_simmulation = 0;
        table->forks = NULL;
        table->nbr_limit_meals = 0;
        table->nbr_philosophers = 0;
        table->philos = NULL;
        table->start_simmulation = 0;
        table->time_to_die = 0;
        table->time_to_eat = 0;
        table->time_to_sleep = 0;
    }
}

void    ft_print_table(t_table table) 
{
        printf("table.nbr_limit_meals = |%ld|\n", table.nbr_limit_meals);
        printf("table.nbr_philosophers = |%ld|\n", table.nbr_philosophers);
        printf("table.time_to_die = |%ld|\n", table.time_to_die);
        printf("table.time_to_eat = |%ld|\n", table.time_to_eat);
        printf("table.time_to_sleep = |%ld|\n", table.time_to_sleep);
}

int main(int argc, char **argv)
{
    t_table table;

    ft_init_table(&table);
    if (argc != 5 && argc != 6)
        error("Invalid number of arguments");
    else
    {
        parsing(argc, argv, &table);
        ft_print_table(table)
    }
    return 0;
}
