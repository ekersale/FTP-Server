/*
** connexion.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/client_src
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 15:01:53 2014 Elliot Kersale
** Last update Mon Apr 14 11:12:21 2014 Elliot Kersale
*/

#include		"client.h"

int			authentificate(int s)
{
  char			str[1024];

  user_identificate(s);
  memset(str, 0, 1024);
  read(s, str, 1024);
  printf("%s\n", str);
  if (strcmp(str, ERR_LOGIN) == 0 || strcmp(str, ERR_MDP) == 0)
    return (EXIT_FAILURE);
  do_actions(s);
  return (EXIT_SUCCESS);
}

int			connect_client(char *ip, char *port)
{
  struct protoent	*proto;
  struct sockaddr_in	sin;
  int			s;
  int			por;
  int			cs;

  por = atoi(port);
  proto = getprotobyname(TCP);
  if ((s = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    {
      perror("client.c l40");
      return (EXIT_FAILURE);
    }
  sin.sin_family = AF_INET;
  sin.sin_port = htons(por);
  sin.sin_addr.s_addr = inet_addr(ip);
  if ((cs = connect(s, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      perror("client.c l48");
      return (EXIT_FAILURE);
    }
  return (authentificate(s));
}
