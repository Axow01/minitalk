SRCS = 

OBJSB = ${SRCSB:.c=.o}

OBJS = ${SRCS:.c=.o}
 
NAME = minitalk.a
 
CC	 = gcc
 
CFLAGS = -Wall -Wextra -Werror
 
all	: ${NAME}
 
${NAME}: ${OBJS}
					@ar -rcs  ${NAME} ${OBJS}
 
clean  :  
					@rm -f ${OBJS} ${OBJSB}
 
fclean : clean
					@rm -f ${NAME}
 
re     : fclean all
