/*
** main.c for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 14:27:19 2014 Elliot Kersale
** Last update Sun Apr 13 16:58:34 2014 Elliot Kersale
*/

#include		"serveur.h"

time_t			start;

void			disconnect()
{
  time_t		end;

  time(&end);
  fprintf(stdout, SDONE, difftime(end, start));
  fflush(stdout);
  exit(EXIT_SUCCESS);
}

void			read_client(t_serv *serv, int cs)
{
  char			str[4096];
  pid_t			pid;

  pid = fork();
  if (pid == 0)
    {
      while (1)
	{
	  memset(str, 0, 4096);
	  if (read(cs, str, 4096) != 0)
	    {
	      if (strcmp(EXIT, str) == 0)
		client_disconnect(serv, cs);
	      if (strcmp(str, GET) == 0)
		send_file(cs);
	      else if (strcmp(str, PUT) == 0)
		recv_file(cs);
	      else
		function_exec(serv, str, cs);
	    }
	}
    }
  return ;
}

int			run_serveur(t_serv *serv)
{
  while (1)
    {
      if ((serv->cs = accept(serv->s, (struct sockaddr *)&(serv->sin_client),
			     (socklen_t *)&(serv->client_len))) == -1)
	  perror("");
      else
	{
	    if (user_identificate(serv) == EXIT_SUCCESS)
	      {
		user_information(serv);
		read_client(serv, serv->cs);
	      }
	}
    }
}

int			init_serveur(t_serv *serv)
{
  if ((serv->s = socket(AF_INET, SOCK_STREAM, serv->proto->p_proto)) == -1)
    {
      perror("");
      return (EXIT_FAILURE);
    }
  if (get_bind(serv) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  start_serv();
  if (my_listen(&serv->s) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  serv->client_len = sizeof(serv->sin_client);
  return (EXIT_SUCCESS);
}

int			connect_serv(char *port)
{
  t_serv		serv;

  time(&start);
  signal(SIGINT, disconnect);
  create_depot();
  serv.port = atoi(port);
  serv.proto = getprotobyname(TCP);
  if (check_port(serv.port) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  if (init_serveur(&serv) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  run_serveur(&serv);
  return (EXIT_SUCCESS);
}
