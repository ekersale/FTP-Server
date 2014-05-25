/*
** display_info.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 17:01:35 2014 Elliot Kersale
** Last update Sun Apr 13 16:58:27 2014 Elliot Kersale
*/

#include		"serveur.h"

void			user_information(t_serv *serv)
{
  write(serv->cs, CONNECT_DONE, strlen(CONNECT_DONE));
  fprintf(stdout, USER_INFO, inet_ntoa(serv->sin_client.sin_addr),
	  ntohs(serv->sin_client.sin_port));
  fflush(stdout);
}

void			client_disconnect(t_serv *serv, int cs)
{
  write(cs, DISCONNECTED, strlen(DISCONNECTED));
  fprintf(stdout,SDISCONNECTED, inet_ntoa(serv->sin_client.sin_addr),
	  ntohs(serv->sin_client.sin_port));
  close(cs);
  exit(-1);
}
