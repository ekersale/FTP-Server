/*
** exec_cmd.c for my_ftp in /home/kersal_e/projet_actuels/PSU_2013_myftp
** 
** Made by Elliot Kersale
** Login   <kersal_e@epitech.net>
** 
** Started on  Fri Apr 11 17:07:51 2014 Elliot Kersale
** Last update Fri Apr 11 18:28:31 2014 Elliot Kersale
*/

#include		"serveur.h"

void			save_std(int *save_stdout, int *save_stderr, int cs)
{
  int			std_tmp;

  std_tmp = cs;
  *save_stdout = dup(STDOUT_FILENO);
  *save_stderr = dup(2);
  dup2(std_tmp, 1);
  dup2(std_tmp, 2);
}

void			check_right(t_serv *serv, int cs)
{
  char			*save;

  if ((save = malloc(4096 * sizeof(char))) == NULL)
    return ;
  getcwd(save, 4096);
  if (chdir(serv->cmd[1]) == -1)
    perror("");
  else if (get_pwd() == NULL)
    {
      write(cs, ERR_PATH, strlen(ERR_PATH));
      chdir(save);
    }
  else
    write(cs, SUCCED, strlen(SUCCED));
}

void			fin_func(int save_stdout, int save_stderr)
{
  dup2(save_stdout, 1);
  dup2(save_stderr, 2);
  close(save_stdout);
  close(save_stderr);
}

void			function_exec(t_serv *serv, char *s, int cs)
{
  int			save_stdout;
  int			save_stderr;

  if (parse_command(s, serv) == EXIT_FAILURE)
    {
      write(cs, ERR_CMD, strlen(ERR_CMD));
      return ;
    }
  save_std(&save_stdout, &save_stderr, cs);
  if (strcmp(serv->cmd[0], PWD) == 0)
    write(cs, get_pwd(), strlen(get_pwd()));
  else if (strcmp(serv->cmd[0], CD) == 0 && serv->cmd[1][0] == 0)
    {
      chdir(DEPOT);
      write(cs, SUCCED, strlen(SUCCED));
    }
  else if (strcmp(serv->cmd[0], CD) == 0 && serv->cmd[1][0] != 0)
    check_right(serv, cs);
  else
    do_fork(cs, serv);
  fin_func(save_stdout, save_stderr);
}
