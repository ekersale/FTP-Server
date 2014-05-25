/*
** main.c for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 14:27:19 2014 Elliot Kersale
** Last update Sun Apr 13 16:55:57 2014 Elliot Kersale
*/

#include		"client.h"

int			load_file(int *n, int fd, int s)
{
  char			str[4096];

  while (*n >= 4096)
    {
      memset(str, 0, 4096);
      if ((*n = read(s, str, 4096)) == -1)
	{
	  close(fd);
	  return (EXIT_FAILURE);
	}
      if (strcmp(str, DONE) != 0)
	write(fd, str, *n);
    }
  close(fd);
  return (EXIT_SUCCESS);
}

int			create_file(char *fname, int *fd)
{
  if (access(fname, R_OK|W_OK) == 0)
    {
      if ((*fd = open(fname, O_RDWR|O_TRUNC, 0644)) == -1)
	  return (EXIT_FAILURE);
    }
  else
    if ((*fd = open(fname, O_CREAT|O_RDWR, 0644)) == -1)
	return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			download_file(char *fname, int s)
{
  char			str[4096];
  int			fd;
  int			n;

  if (fname == NULL)
    return (EXIT_FAILURE);
  read(s, str, 4096);
  if (strcmp(str, "ok") != 0)
    return (EXIT_FAILURE);
  write(s, fname, strlen(fname));
  memset(str, 0, 4096);
  read(s, str, 4096);
  if (strcmp(str, ERR_FILE) == 0)
    return (EXIT_SUCCESS);
  if (create_file(fname, &fd) == EXIT_FAILURE)
    return (EXIT_SUCCESS);
  write(s, "ok", 2);
  memset(str, 0, 4096);
  if ((n = read(s, str, 4096)) == -1)
    return (EXIT_FAILURE);
  write(fd, str, n);
  load_file(&n, fd, s);
  return (EXIT_SUCCESS);
}
