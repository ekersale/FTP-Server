/*
** commands.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/client_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 15:08:35 2014 Elliot Kersale
** Last update Sun Apr 13 16:31:53 2014 Elliot Kersale
*/

#include		"client.h"

void			prompt(char **str, char **tmp)
{
  fflush(stdout);
  printf(PROMPT);
  fflush(stdout);
  memset(*str, 0, 4096);
  memset(*tmp, 0, 4096);
  if (read(0, *str, 4096) == -1)
    return ;
  strcpy(*tmp, *str);
}

int			my_malloc(char **str, char **tmp)
{
  if ((*tmp = malloc(4096 * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  if ((*str = malloc(4096 * sizeof(char))) == NULL)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			checks(char **str, char **tmp, int s)
{
  if (check_command(s, *str) == EXIT_FAILURE)
    {
      write(s, *tmp, strlen(*tmp));
      if (strcmp(CEXIT, *tmp) == 0)
	{
	  read(s, *str, 4096);
	  printf("%s", *str);
	  fflush(stdout);
	  close(s);
	  return (EXIT_FAILURE);
	}
      memset(*str, 0, 4096);
      read(s, *str, 4096);
      printf("%s", *str);
    }
  return (EXIT_SUCCESS);
}

void			do_actions(int s)
{
  char			*str;
  int			i;
  char			*tmp;

  i = 0;
  if (my_malloc(&str, &tmp) == EXIT_FAILURE)
    return ;
  while (i == 0)
    {
      prompt(&str, &tmp);
      if (strcmp(str, "\n") != 0)
	{
	  if (checks(&str, &tmp, s) == EXIT_FAILURE)
	    return ;
	}
    }
  return ;
}

int			check_command(int s, char *cmd)
{
   char			*token;
   int			i;

   token = strtok(cmd, " ") ;
   i = 0;
   while (token != NULL)
     {
       if (strcmp(token, GET) == 0 && i == 0)
	 {
	   if (write(s, GET, strlen(GET)) == -1)
	     return (error(""));
	   return (download_file(strtok(NULL, "\n"), s));
	 }
       else if (strcmp(token, PUT) == 0 && i == 0)
	 {
	   if (write(s, PUT, strlen(PUT)) == -1)
	     return (error(""));
	   return (upload_file(strtok(NULL, "\n"), s));
	 }
       else
	 return (EXIT_FAILURE);
    }
  return (EXIT_FAILURE);
}
