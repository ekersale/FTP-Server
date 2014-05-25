/*
** authentification.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 15:24:16 2014 Elliot Kersale
** Last update Fri Apr 11 15:25:01 2014 Elliot Kersale
*/

#include		"client.h"

int			login(int s)
{
  char			str[4096];

  memset(str, 0, 4096);
  if (read(s, str, 4096) == -1)
    return (error(LOGIN));
  printf("%s", str);
  fflush(stdout);
  memset(str, 0, 4096);
  if (read(0, str, 4096) == -1)
    return (error(LOGIN));
  if (write(s, str, strlen(str)) == -1)
    return (error(LOGIN));
  return (EXIT_SUCCESS);
}

int			user_identificate(int s)
{
  if (login(s) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (login(s) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
