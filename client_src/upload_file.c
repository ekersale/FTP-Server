/*
** upload_file.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/client_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Sun Apr 13 16:30:54 2014 Elliot Kersale
** Last update Sun Apr 13 16:34:47 2014 Elliot Kersale
*/

#include		"client.h"

char			*reverse(char *fname)
{
  char			*fin;
  int			i;
  int			n;

  i = strlen(fname) - 1;
  n = 0;
  if ((fin = malloc(strlen(fname) * sizeof(char))) == NULL)
    return (NULL);
  while (i >= 0)
    {
      fin[n] = fname[i];
      n++;
      i--;
    }
  fin[n] = '\0';
  return (fin);
}

char			*get_file_name(char *path)
{
  char			*fname;
  int			i;
  int			n;

  i = strlen(path) - 1;
  n = 0;
  if ((fname = malloc(strlen(path) * sizeof(char))) == NULL)
    return (NULL);
  memset(fname, 0, strlen(path));
  while (i >= 0)
    {
      if (path[i] == '/')
	{
	  fname[n] = '\0';
	  return (reverse(fname));
	}
      fname[n] = path[i];
      n++;
      i--;
    }
  fname[n] = '\0';
  return (reverse(fname));
}

int			my_exit(int fd)
{
  close(fd);
  return (EXIT_FAILURE);
}

int			send_data(int fd, int s)
{
  char			buff[4096];
  int			n;

  if ((n = read(fd, buff, 4096)) == -1)
    return (my_exit(fd));
  write(s, buff, n);
  while (n >= 4096)
    {
      memset(buff, 0, 4096);
      if ((n = read(fd, buff, 4096)) == -1)
	return (my_exit(fd));
      write(s, buff, n);
    }
  if (n == 0)
    write(s, DONE, strlen(DONE));
  close(fd);
  return (EXIT_SUCCESS);
}

int			upload_file(char *file, int s)
{
  int			fd;
  char			*fname;
  char			buff[4096];

  if (read(s, buff, 4096) == -1 && strcmp(buff, "ok") != 0)
    return (EXIT_FAILURE);
  memset(buff, 0, 4096);
  if ((fd = open(file, O_RDONLY)) == -1 ||
      (fname = get_file_name(file)) == NULL)
    {
      close(fd);
      write(s, ERR_FILE, strlen(ERR_FILE));
      return (error(""));
    }
  write(s, fname, strlen(fname));
  if (read(s, buff, 4096) == -1)
    return (my_exit(fd));
  if (strcmp(buff, "ok") != 0)
    return (my_exit(fd));
  return (send_data(fd, s));
}
