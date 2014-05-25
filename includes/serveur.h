/*
** serveur.h for myftp in /home/kersal_e/projet_actuels/PSU_2013_myftp/sources
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Mon Mar 24 16:56:06 2014 Elliot Kersale
** Last update Sun Apr 13 17:13:57 2014 Elliot Kersale
*/

#ifndef			_SERVEUR_H__
# define		_SERVEUR_H__
/*
** INCLUDES
*/
#include                <sys/types.h>
#include                <sys/socket.h>
#include                <unistd.h>
#include                <stdlib.h>
#include                <string.h>
#include                <netdb.h>
#include		<time.h>
#include		<stdio.h>
#include                <netinet/in.h>
#include                <arpa/inet.h>
#include		<signal.h>
#include		<sys/stat.h>
#include		<fcntl.h>
/*
** DEFINES
*/
# define		START_SERVER		"\033[32mServeur start on : %s\n\033[0m"
# define		INCORRECT_PORT		"\033[31mPort %d: Cannot connect (not a registered port)\033[0m"
# define		USER_INFO		"\033[33mHost : %s -- Port : %d --> Connected\n\033[0m"
# define		CONNECT_DONE		"Connection is established"	
# define		CANNOT_CONNECT		"\033[31mHost : %s -- Port : %d --> Cannot connect, limit reached\n\033[0m"
# define		CONNECT			"\033[33mHost : %s -- Port : %d --> Connected\n\033[0m"
# define		SDISCONNECTED		"\033[31mHost : %s -- Port : %d --> Disconnect\n\033[0m"
# define		DISCONNECTED		"Connection is disconnected\n"
# define		SDONE			"\r   \n\033[32mServer disconnection - Execution time : %.0f secondes\n\033[0m"
# define                ERR_READ                "File can't be fined or unreadable"
# define		DEPOT			"./depot"
# define		CRYPT_KEY		"6b2ded51d81a4403d8a4bd25fa1e57ee"
# define		ERR_PATH		"incorrect path\n"
# define		SUCCED			"succed\n"
# define		ERR_CMD			"command not found\n"
# define		ERR_MDP			"Mdp incorrect"
# define		ERR_LOGIN		"Login incorrect"
# define		SESSION_FILE		"../sessions"
# define		LOGIN			"login :"
# define		MDP			"mdp :"
# define		DEPOT			"./depot"
# define		TCP			"TCP"
# define		EXIT			"exit\n"
# define		GET			"get"
# define		PWD			"pwd"
# define		CD			"cd"
# define		PUT			"put"
# define		ERR_FILE		"No such file or directory"
# define		DOWNLOADING		"\033[36mDownloading file : %s\n\033[0m"
# define		UPLOADING		"\033[36mUploading file : %s\n\033[0m"
# define		FAIL			"fail"
# define		OK			"ok"
# define		ERR_OCCU		"An error was occured\n"
/*
** STRUCTURE
*/
typedef	struct		s_serv
{
  struct protoent       *proto;
  struct sockaddr_in    sin_client;
  int                   client_len;
  int                   s;
  int                   port;
  int                   cs;
  char                  *str;
  char			cmd[2][50];
  char			*login;
  char			*mdp;
}			t_serv;
/*
** serveur.c
*/
int                     connect_serv(char *);
int			run_serveur(t_serv *);
void			read_client(t_serv *, int);
void			client_disconnect(t_serv *, int);
int			init_serveur(t_serv *);
/*
** send_recv.c
*/
int			recv_data(int, int);
int			recv_file(int);
int			send_file(int);
int			my_exit(int, int);
int			send_data(int, int);
/*
** display_info.c
*/
void			disconnect();
void			user_information(t_serv *);
/*
** parse_cmd.c
*/
int			parse_command(char *, t_serv *);
/*
** init_func.c
*/
int                     check_port(int);
int                     get_bind(t_serv *);
void                    start_serv();
int                     my_listen(int *);
/*
** my_error.c
*/
int			my_error(char *);
int	   		create_depot();
/*
** authentification.c
*/
int			check_info(FILE *, char **, t_serv *);
int			user_identificate(t_serv *);
int			check_authentification(char *, char *, t_serv *);
/*
** get_pwd.c
*/
char			*get_pwd();
int			my_init(char **, char **, int *, int *);
/*
** cmd_fork.c
*/
void			proc_father(int, int, int);
void			proc_son(int, t_serv *);
void			do_fork(int, t_serv *);
/*
** exec_cmd.c
*/
void			function_exec(t_serv *, char *, int);
void			fin_func(int, int);
void			check_right(t_serv *, int);
void			save_std(int *, int *, int);
/*
**
*/
#endif		/*	_SERVEUR_H__   	*/
