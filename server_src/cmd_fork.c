/*
** cmd_fork.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 18:12:57 2014 Elliot Kersale
** Last update Fri Apr 11 18:28:15 2014 Elliot Kersale
*/

#include		"serveur.h"

void			proc_father(int cs, int pipefd1, int pipefd0)
{
  int			std_tmp;
  char			*buff;

  if ((buff = malloc(4096 * sizeof(char))) == NULL)
    return ;
  std_tmp = cs;
  dup2(std_tmp, 1);
  dup2(std_tmp, 2);
  close(pipefd1);
  memset(buff, 0, 4096);
  if (read(pipefd0, buff, 4096) == 0)
    write(cs, "\0", 1);
  else
    write(std_tmp, buff, 4096);
  close(pipefd0);
  dup2(std_tmp, 1);
  dup2(std_tmp, 2);
}

void			proc_son(int pipefd, t_serv *serv)
{
  dup2(pipefd, 1);
  dup2(pipefd, 1);
  if (strcmp(serv->cmd[0], "ls") == 0 && serv->cmd[1][0] == 0)
    execlp("ls", "ls", NULL);
  else
    execlp(serv->cmd[0], serv->cmd[0], serv->cmd[1], NULL);
  exit(-1);
}

void			do_fork(int cs, t_serv *serv)
{
  int			pipefd[2];
  pid_t			pid;

  pipe(pipefd);
  pid = fork();
  if (pid == 0)
    proc_son(pipefd[1], serv);
  else
    proc_father(cs, pipefd[1], pipefd[0]);
}
