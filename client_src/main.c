/*
** main.c for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 19:28:21 2014 Elliot Kersale
** Last update Mon Mar 24 19:29:23 2014 Elliot Kersale
*/

#include		"client.h"

int			main(int ac, char **av)
{
  if (ac != 3)
    {
      fprintf(stderr, "Usage : ./serveur [ip] [port]\n");
      return (EXIT_FAILURE);
    }
  connect_client(av[1], av[2]);
  return (EXIT_SUCCESS);
}
