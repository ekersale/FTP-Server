/*
** my_error.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 16:39:36 2014 Elliot Kersale
** Last update Fri Apr 11 16:47:54 2014 Elliot Kersale
*/

#include		"serveur.h"

int			my_error(char *s)
{
  perror(s);
  return (EXIT_FAILURE);
}
