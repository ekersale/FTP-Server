##
## Makefile for epikong in /home/kersal_e/rush-epikong
## 
## Made by Elliot Kersale
## Login   <kersal_e@epitech.net>
## 
## Started on  Fri Mar  7 20:47:19 2014 Elliot Kersale
## Last update Mon Apr 14 19:51:04 2014 Elliot Kersale
##

##################SERVER#####################

SERV_NAME	=	server

SERV_SRCS	=	./server_src/main.c		\
			./server_src/serveur.c		\
			./server_src/init_func.c	\
			./server_src/my_error.c		\
			./server_src/authentification.c	\
			./server_src/display_info.c	\
			./server_src/send_recv.c	\
			./server_src/exec_cmd.c		\
			./server_src/parse_cmd.c	\
			./server_src/get_pwd.c		\
			./server_src/cmd_fork.c

SERV_OBJS	=	$(SERV_SRCS:.c=.o)

$(SERV_NAME)	:	$(SERV_OBJS)
			$(CC) $(SERV_OBJS) -o $(SERV_NAME)

#################CLIENT#####################

CLIENT_NAME	=	client

CLIENT_SRCS	=	./client_src/main.c		\
			./client_src/client.c		\
			./client_src/connexion.c	\
			./client_src/my_error.c		\
			./client_src/commands.c		\
			./client_src/authentification.c	\
			./client_src/upload_file.c

CLIENT_OBJS	=	$(CLIENT_SRCS:.c=.o)

$(CLIENT_NAME)	:	$(CLIENT_OBJS)
			$(CC) $(CLIENT_OBJS) -o $(CLIENT_NAME)

################ALL########################

CC		=	gcc

INC		=	./includes

CFLAGS		=	-Wall -W -Werror -I $(INC)

RM		=	rm -rf

all		:	$(SERV_NAME) $(CLIENT_NAME)

clean		:
			$(RM) $(CLIENT_OBJS)
			$(RM) $(SERV_OBJS)

fclean		:	clean
			$(RM) $(SERV_NAME)
			$(RM) $(CLIENT_NAME)

re		:	fclean all
