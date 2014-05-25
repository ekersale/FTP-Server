/*
** client.h for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 19:29:59 2014 Elliot Kersale
** Last update Sun Apr 13 16:33:37 2014 Elliot Kersale
*/

#ifndef			_CLIENT_H__
# define		_CLIENT_H__
/*
** INCLUDES
*/
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		<string.h>
#include		<netdb.h>
#include		<stdio.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<sys/stat.h>
#include		<fcntl.h>
/*
** DEFINE
*/
# define		DONE		"6b2ded51d81a4403d8a4bd25fa1e57ee"
# define		GET		"get"
# define		PROMPT		"\033[35m$>\033[0m "
# define		LOGIN		"login"
# define		TCP		"TCP"
# define		ERR_LOGIN	"Login incorrect"
# define		ERR_MDP		"Mdp incorrect"
# define		CEXIT		"exit\n"
# define		PUT		"put"
# define		ERR_FILE	"No such file or directory"
# define                ERR_READ	"File can't be fined or unreadable"
/*
** client.c
*/
int			download_file(char *, int);
int			cpy_newfile(int, int, int);
/*
** my_error.c
*/
int			error(char *);
/*
** commands.c
*/
void			do_actions(int);
int			check_command(int, char *);
void			prompt(char **, char **);
int			my_malloc(char **, char **);
int			checks(char **, char **, int);
/*
** upload_file.c
*/
char			*reverse(char *);
char			*get_file_name(char *);
int			my_exit(int);
int			send_data(int, int);
int			upload_file(char *, int);
/*
** authentification.c
*/
int			user_identificate(int);
int			login(int);
/*
** connexion.c
*/
int			connect_client(char *, char *);

#endif		/*	_CLIENT_H__	*/
