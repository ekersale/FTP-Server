/*
** send_recv.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 17:03:04 2014 Elliot Kersale
** Last update Sun Apr 13 17:17:49 2014 Elliot Kersale
*/

#include		"serveur.h"

int			recv_data(int cs, int fd)
{
  char			fname[4096];
  int			n;
  
  memset(fname, 0, 4096);
  if ((n = read(cs, fname, 4096)) == -1)
    return (my_exit(fd, cs));
  write(fd, fname, n);
  while (n >= 4096)
    {
      memset(fname, 0, 4096);
      if ((n = read(cs, fname, 4096)) == -1)
	return (my_exit(fd, cs));
      if (strcmp(fname, CRYPT_KEY) != 0)
	write(fd, fname, n);
    }
  close(fd);
  return (EXIT_SUCCESS);
}

int			recv_file(int cs)
{
  char			fname[4096];
  int			fd;

  write(cs, OK, strlen(OK));
  memset(fname, 0, 4096);
  if (read(cs, fname, 4096) == -1)
    return (EXIT_FAILURE);
  printf(DOWNLOADING, fname);
  if (strcmp(fname, ERR_FILE) == 0)
      return (EXIT_FAILURE);
  if ((fd = open(fname, O_CREAT|O_RDWR, 0644)) == -1)
    {
      write(cs, FAIL, strlen(FAIL));
      return (EXIT_FAILURE);
    }
  write(cs, OK, strlen(OK));
  return (recv_data(cs, fd));
}

int			my_exit(int fd, int s)
{
  write(s, ERR_OCCU, strlen(ERR_OCCU));
  close(fd);
  return (EXIT_FAILURE);
}

int			send_data(int fd, int s)
{
  char			buff[4096];
  int			n;

  memset(buff, 0, 4096);
  if ((n = read(fd, buff, 4096)) == -1)
    return (my_exit(fd, s));
  write(s, buff, n);
  while (n >= 4096)
    {
      memset(buff, 0, 4096);
      if ((n = read(fd, buff, 4096)) == -1)
	return (my_exit(fd, s));
      write(s, buff, n);
    }
  if (n == 0)
    write(s, CRYPT_KEY, strlen(CRYPT_KEY));
  close(fd);
  return (EXIT_SUCCESS);
}

int			send_file(int s)
{
  int			fd;
  char			fname[4096];
  char			buff[4096];

  write(s, OK, strlen(OK));
  memset(fname, 0, 4096);
  read(s, fname, 4096);
  if ((fd = open(fname, O_RDONLY)) == -1)
    {
      write(s, "No such file or directory\n", 26);
      return (my_error(""));
    }
  write(s, OK, strlen(OK));
  printf(UPLOADING, fname);
  if (read(s, buff, 4096) == -1)
    return (my_exit(fd, s));
  if (strcmp(buff, OK) != 0)
    return (my_exit(fd, s));
  return (send_data(fd, s));
}
