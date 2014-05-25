/*
** authentification.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 16:40:44 2014 Elliot Kersale
** Last update Fri Apr 11 16:57:36 2014 Elliot Kersale
*/

#include		"serveur.h"

int			check_info(FILE *fd, char **buff, t_serv *serv)
{
  size_t       		nbyte;

  nbyte = 50;
  if (strcmp(*buff, serv->login) == 0)
    {
      memset(*buff, 0, strlen(serv->login));
      getline(buff, &nbyte, fd);
      if (strcmp(*buff, serv->mdp) == 0)
	{
	  fclose(fd);
	  return (EXIT_SUCCESS);
	}
      write(serv->cs, ERR_MDP, strlen(ERR_MDP));
      fclose(fd);
      return (EXIT_FAILURE);
    }
  return (2);
}

int			check_authentification(char *login, char *mdp, t_serv *serv)
{
  FILE			*fd;
  int       		nb;
  char			*buff;
  size_t       		nbyte;
  int			ret;

  buff = NULL;
  nbyte = 50;
  serv->login = login;
  serv->mdp = mdp;
  if ((fd = fopen(SESSION_FILE, "r")) == NULL)
    return (my_error(""));
  while ((nb = getline(&buff, &nbyte, fd)) != -1)
    {
      if ((ret = check_info(fd, &buff, serv)) != 2)
	{
	  if (ret == EXIT_SUCCESS)
	    return (EXIT_SUCCESS);
	  else
	    return (EXIT_FAILURE);
	}
    }
  fclose(fd);
  write(serv->cs, ERR_LOGIN, strlen(ERR_LOGIN));
  return (EXIT_FAILURE);
}

int			user_identificate(t_serv *serv)
{
  char			login[4096];
  char			mdp[4096];

  memset(login, 0, 4096);
  memset(mdp, 0, 4096);
  write(serv->cs, LOGIN, strlen(LOGIN));
  read(serv->cs, login, 4096);
  write(serv->cs, MDP, strlen(MDP));
  read(serv->cs, mdp, 4096);
  if (check_authentification((char *)login, (char *)mdp, serv) == EXIT_SUCCESS)
    return (EXIT_SUCCESS);
  return (EXIT_FAILURE);
}
