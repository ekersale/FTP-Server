/*
** parse_cmd.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 17:09:32 2014 Elliot Kersale
** Last update Fri Apr 11 17:13:34 2014 Elliot Kersale
*/

#include		"serveur.h"

int			parse_command(char *s, t_serv *serv)
{
  char			*token;

  token = strtok(s, " ");
  memset(serv->cmd[0], 0, 50);
  memset(serv->cmd[1], 0, 50);
  while (token != NULL)
    {
      if (strcmp(token, CD) == 0 || strcmp(token, "ls") == 0)
	{
	  strcpy(serv->cmd[0], token);
	  token = strtok(NULL, "\0");
	  if (token != NULL)
	    strncpy(serv->cmd[1], token, strlen(token) - 1);
	  return (EXIT_SUCCESS);
	}
      if (strcmp(token, "cd\n") == 0 || strcmp(token, "ls\n") == 0
	  || strcmp(token, "pwd\n") == 0)
	{
	  strncpy(serv->cmd[0], token, strlen(token) - 1);
	  return (EXIT_SUCCESS);
	}
      return (EXIT_FAILURE);
    }
  return (EXIT_FAILURE);
}
