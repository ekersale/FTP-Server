/*
** get_pwd.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 17:08:54 2014 Elliot Kersale
** Last update Fri Apr 11 17:38:33 2014 Elliot Kersale
*/

#include		"serveur.h"

int			my_init(char **tmp, char **pwd, int *i, int *n)
{
  *i = 0;
  *n = 0;
  if ((*tmp = malloc(4096 * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  if ((*pwd = malloc(4096 * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  memset(*tmp, 0, 4096);
  getcwd(*tmp, 4096);
  return (EXIT_SUCCESS);
}

char			*get_pwd()
{
  char			*pwd;
  int			i;
  int			n;
  char			*tmp;

  if (my_init(&tmp, &pwd, &i, &n) == EXIT_FAILURE)
    return (NULL);
  while (tmp[i] != '\0')
    {
      if (tmp[i + 1] == 'd' && tmp[i + 2] == 'e' && tmp[i + 3] == 'p'
	  && tmp[i + 4] == 'o' && tmp[i + 5] == 't')
	{
	  while (tmp[i] != '\0')
	    {
	      pwd[n] = tmp[i];
	      i++;
	      n++;
	    }
	  pwd[n] = '\n';
	  fflush(stdout);
	  return (pwd);
	}
      i++;
    }
  return (NULL);
}
